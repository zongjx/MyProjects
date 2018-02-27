<%@page language="java" contentType="text/html; charset=utf-8"%>
<%@page import="java.io.*,java.util.*,org.apache.commons.io.*,java.sql.*"%>
<%@page import="org.apache.commons.fileupload.*"%>
<%@page import="org.apache.commons.fileupload.disk.*"%>
<%@page import="org.apache.commons.fileupload.servlet.*"%>
<%request.setCharacterEncoding("utf-8");%>
<%!
	String user;
	String name;
	String pic;
	String price;
	String info;
	String cla;
	Integer quantity;
	String submit;
%>
<%
	user = request.getParameter("user");
	pic = "goods/";
	
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	String msg = "";
	if(request.getMethod().equalsIgnoreCase("post")){	
		boolean isMultipart = ServletFileUpload.isMultipartContent(request);
		if(isMultipart) {
			FileItemFactory factory = new DiskFileItemFactory();
			ServletFileUpload upload = new ServletFileUpload(factory);
			List items = upload.parseRequest(request);
			for(int i = 0; i < items.size(); i++) {
				FileItem fi = (FileItem) items.get(i);
				if(fi.isFormField()) {
					if(fi.getFieldName().equals("name")){
						name = fi.getString("utf-8");
					}
					else if(fi.getFieldName().equals("price")){
						price = fi.getString("utf-8");
					}
					else if(fi.getFieldName().equals("info")){
						info = fi.getString("utf-8");
					}
					else if(fi.getFieldName().equals("class")){
						cla = fi.getString("utf-8");
					}
					else if(fi.getFieldName().equals("quantity")){
						quantity = Integer.valueOf(fi.getString("utf-8"));
					}
					else if(fi.getFieldName().equals("submit")){
						submit = fi.getString("utf-8");
					}
				}
				else{
					DiskFileItem dfi = (DiskFileItem) fi;
					if(!dfi.getName().trim().equals("")) {
						String fileName = application.getRealPath("/goods/")
						+ FilenameUtils.getName(dfi.getName());
						pic = pic+FilenameUtils.getName(dfi.getName());
						dfi.write(new File(fileName));
					}				
				}
			} 
		}	
		if(submit != null){
			Class.forName("com.mysql.jdbc.Driver");
			Connection con = DriverManager.getConnection(connectString,users, pwd);
			Statement stmt = con.createStatement();
			try{ 
				String fmt="insert into goods(name,price,info,pic,class,quantity) values('%s','%s','%s','%s','%s','%d');";
				String sql = String.format(fmt,name,price,info,pic,cla,quantity);
				int cnt = stmt.executeUpdate(sql);
				stmt.close(); con.close();
			}catch (Exception e){
				msg = e.getMessage();
			}
			
			response.sendRedirect("GoodList.jsp?user="+user);
		}
		else {
			response.sendRedirect("GoodList.jsp?user="+user);
		}
	}	
%>

<!DOCTYPE HTML>
<html>
	<head>
	<title>创建新物品</title>
	<style>
		body {
			background:url(images/bk1.jpg);
			background-repeat:no-repeat;
			background-size:cover;
		}
		#main{
			margin: 0 auto;
			width:750px;
			height:250px;
			position:relative;
			top:120px;
			border:solid 2px black;
			padding:20px;
			border-radius:20px;
			z-index:3;
			background:white;
			box-shadow:inset -3px 3px 2px #AAAAAA,-3px 3px 2px #999;
		}
		#btn {
			margin: 0 auto;
			width:200px;
			padding-top:20px;
		}
		#exit {
			margin-left:20px;
		}
	</style>
	</head>
	<body>
		<div id="main">
			<form action="add.jsp?user=<%=user%>" method="post" enctype="multipart/form-data" name="addGoods">
				<span style="font-weight:bold;">物品名称：</span><input type="text" name="name"><br/>
				<p><span style="font-weight:bold;">商品图片：</span><input type="file" name="pic"></p>
				<p><span style="font-weight:bold;">物品价格：</span><input type="text" name="price"></p>
				<p><span style="font-weight:bold;">物品简介：</span><input type="text" name="info"></p>
				<p><span style="font-weight:bold;">物品数量：</span><input type="text" name="quantity"></p>
				<p><span style="font-weight:bold;">物品分类：</span><input type="radio" name="class" value="服装饰品">服装饰品&nbsp&nbsp
				<input type="radio" name="class" value="童装玩具">童装玩具&nbsp&nbsp
				<input type="radio" name="class" value="生活百货">生活百货&nbsp&nbsp
				<input type="radio" name="class" value="运动户外">运动户外&nbsp&nbsp
				<input type="radio" name="class" value="数码优品">数码优品&nbsp&nbsp
				<input type="radio" name="class" value="文教乐器">文教乐器&nbsp&nbsp</p>
				<p id="btn">
					<input type=submit name="submit" value="保存" id="save">
					<input type=submit name="exit" value="返回" id="exit">
				</p>
			</form>
		</div>
		
	</body>
</html>
