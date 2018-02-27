<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
	<%! 
		String user;
		String goods_id;
	%>
	<% 
		request.setCharacterEncoding("utf-8");
		String msg ="";
		String flag = "";
		user = request.getParameter("user");
		// 连接数据库
		String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
		String users="root";
		String pwd="123456";
		//String shuru = request.getParameter("num");
		StringBuilder table = new StringBuilder();
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			String str;
			//str = "select * from goods where id in (select good_id from buy where user = \"" + user + "\") limit " + pres.toString() + "," + pgcnt.toString();
			str = "select * from buy where user = \"" + user + "\" " ;
			ResultSet rs = stmt.executeQuery(str);	
			table.append("<table border=\"0\"><tr><th>商品图片</th><th>商品名称</th><th>价格</th>"+"<th> 分类 </th><th>选项</th></tr>");
			while(rs.next()) {
				flag = "1";
				table.append(String.format(
							"<tr><td><img id=\"pic\" src=\"%s\"></td><td>%s</td><td>%s</td><td>%s</td><td>%s %s</td></tr>",
							rs.getString("good_pic"),
							rs.getString("good_name"),
							rs.getString("good_price"),
							rs.getString("good_class"),
							"<a class=\"linked\" href='goodDetail.jsp?user=" + user + "&id="+rs.getString("good_id")+"' style=\"text-decoration:none; \">查看详细信息</a>",
							"<a class=\"linked\" href='delete.jsp?user=" + user + "&id="+rs.getString("id")+"&dtype=buy' style=\"text-decoration:none; color:red;\">&nbsp &nbsp删除</a>"));
							
							
			}
			table.append("</table>");
			rs.close(); stmt.close(); con.close();
		}
		catch (Exception e){
			msg = e.getMessage();
		}
	%>
	
	
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>我的购物车</title>
	</head>
	
	<style>
		table{
			position: relative;
			top: 80px;
			width: 700px;
			left: -80px;
			background:white;
			border-radius:10px;
		}
		td,th{
			border: solid grey 1px;
			margin: 0 0 0 0;
			padding: 10px 10px 10px 10px
		}
		.container{
			margin:0 auto;
			width:500px;
			text-align:center;
		}
		#pic {
			width:80px;
			height:80px;
		}
		a:link,a:visited {
			color:blue;
		}
		#btn {
			position:relative;
			top:30px;
			left:0px;
		}
		body {
			background:url(images/buy2.jpg);
		}
			
	</style>
	
	<body>
		<div class="container">	
			<div id="btn">
				<a href="GoodList.jsp?user=<%=user%>" style="text-decoration:none; border: solid white 2px; border-radius: 8px; background:PeachPuff; padding:8px;color:black;font-weight:bold;" >返回</a>
			</div>
			<%=table%>
			<br/><br/>
		</div>
		</div>
	</body>
</html>

	
