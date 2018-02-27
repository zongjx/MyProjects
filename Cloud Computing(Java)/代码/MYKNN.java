import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URI;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IOUtils;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.mapreduce.lib.partition.HashPartitioner;


//实现KNN算法并应用于分类问题
public class MYKNN
{   
    public static String path1 ;
    public static String path2 ;  
	  
	public static class MyMapper extends Mapper<LongWritable, Text, Text, Text>	//继承mapper
	{
		public ArrayList<Instance> trainSet = new ArrayList<Instance>();
		public int k = 20; 														//k在这里可以根据KNN算法实际要求取值

		protected void setup(Context context)throws IOException, InterruptedException
		{
			FileSystem fileSystem = null;  
			try  
			{  
				fileSystem = FileSystem.get(new URI("hdfs://Master:9000/"), new Configuration());   //训练集路径
			} 
			catch (Exception e){}  
			FSDataInputStream fr0 = fileSystem.open(new Path("trainData.txt"));   //从hdfs上面获取训练集
			BufferedReader fr1 = new BufferedReader(new InputStreamReader(fr0));  //读入文件

			String str = fr1.readLine();  //读行
			while(str!=null)            //逐行读取训练集然后加到trainSet后面
			{  
				Instance trainInstance = new Instance(str);//创建实例
				trainSet.add(trainInstance); //加入训练集实例
				str = fr1.readLine();  
			}   
		}

		protected void map(LongWritable k1, Text v1,Context context)throws IOException, InterruptedException
		{
			ArrayList<Double> distance = new ArrayList<Double>(k);
			ArrayList<String>  trainLable = new ArrayList<String>(k);
			for(int i=0;i<k;i++)
			{
			  distance.add(Double.MAX_VALUE);             //初始化最大距离
			  trainLable.add(String.valueOf(-1.0));       //初始化最小的标签
			}
			Instance testInstance = new Instance(v1.toString());
			for(int i=0;i<trainSet.size();i++)
			{
			   //计算测试集和训练集的欧氏距离
				double dis = Distance.EuclideanDistance(trainSet.get(i).getAttributeset(),testInstance.getAttributeset());

				for(int j=0;j<k;j++)
				{
					if(dis <(Double) distance.get(j))
					{
						distance.set(j, dis);                              
						trainLable.set(j,trainSet.get(i).getLable()+"");    //找出k个距离最近的训练样本，并把标签放在字符串数组里
						break;
					}
				} 
			}  
			for(int i=0;i<k;i++)
			{
			   context.write(new Text(v1.toString()),new Text(trainLable.get(i)+"")); //写入进入reducer进行分类
			}
		}
	}
	 
	 
	public static class MyReducer  extends Reducer<Text, Text, Text, NullWritable>
	{
		protected void reduce(Text k2, Iterable<Text> v2s,Context context)throws IOException, InterruptedException
		{
			  String predictlable ="";  
			  ArrayList<String> arr = new ArrayList<String>();
			  for (Text v2 : v2s)
			  { 
				  arr.add(v2.toString());   
			  }
			  predictlable = MostFrequent(arr);//前k个预测结果的众数作为预测值
			  String  preresult = k2.toString()+"\t"+predictlable+"\r\n";//根据predictlable和实际情况进行修改输出
			  context.write(new Text(preresult),NullWritable.get());
		} 
		
		public String MostFrequent(ArrayList arr)             //求众数函数
		{
			HashMap<String, Double> tmp = new HashMap<String,Double>();
			for(int i=0;i<arr.size();i++)
			{
				if(tmp.containsKey(arr.get(i)))             //统计频率，出现一次label就增加1次数
				{
					 double frequence = tmp.get(arr.get(i))+1;   //频数加一
					 tmp.remove(arr.get(i));                     
					 tmp.put((String) arr.get(i),frequence);     //更新数据集
				}
				else
					tmp.put((String) arr.get(i),new Double(1));  //加入数据集
			}
			Set<String> s = tmp.keySet();

			Iterator it = s.iterator();
			double lablemax=Double.MIN_VALUE;
			String predictlable = null;
			while(it.hasNext())                               //取出众数
			{
			   String key = (String) it.next(); 
			   Double lablenum = tmp.get(key);
			   if(lablenum > lablemax)
			   {
					lablemax = lablenum;
					predictlable = key;
			   }
			}
			return predictlable;                              //返回出现最多的key
		}
	}

	public static void main(String[] args) throws Exception
	{
		FileSystem fileSystem = FileSystem.get(new Configuration());

		path1 = args[0];     //输入
		path2 = args[1]; 	   //输出
		if(fileSystem.exists(new Path(path2)))
		{
		  fileSystem.delete(new Path(path2), true);
		}

		Job job = new Job(new Configuration(),"KNN");
		job.setJarByClass(MYKNN.class);
		FileInputFormat.setInputPaths(job, new Path(path1));//在指令传入的两个参数一个是测试文本，另一个是输出。
		job.setInputFormatClass(TextInputFormat.class);//设置输入格式
		job.setMapperClass(MyMapper.class);//设置mapper类
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(Text.class);
		job.setNumReduceTasks(1);
		job.setPartitionerClass(HashPartitioner.class);
		job.setReducerClass(MyReducer.class);//设置reducer类
		job.setOutputKeyClass(Text.class);//下面是设置输出
		job.setOutputValueClass(NullWritable.class);
		job.setOutputFormatClass(TextOutputFormat.class);
		FileOutputFormat.setOutputPath(job, new Path(path2));//
		System.exit(job.waitForCompletion(true)?0:1);//提交到JobTracker     
		//job.waitForCompletion(true);     
	}
}


class Distance         //距离类    
{
	public static double EuclideanDistance(double[] a,double[] b)      //计算测试样本与训练样本之间的欧式距离
	{
	   double sum = 0.0;
	   for(int i=0;i<a.length;i++)
	   {
		   sum += Math.pow(a[i]-b[i],2);   
	   }    
	   return Math.sqrt(sum);
	}
}


class Instance                            //实例类    从数据集里读取矩阵和每一行的标签字符串数组的函数
{
	public double[] attributeset;//存放样例属性
	public double lable;         //存放样例标签
	public  Instance(String line)
	{
		String[] splited = line.split("\t");
		attributeset = new double[splited.length-1];
		for(int i=0;i<attributeset.length;i++)
		{
			  attributeset[i] = Double.parseDouble(splited[i]);  
		}
		lable = Double.parseDouble(splited[splited.length-1]);      
	}
	public double[] getAttributeset()         //数据集
	{
	   return attributeset; 
	}
	public double getLable()                  //标签
	{
		return lable;
	}
}
