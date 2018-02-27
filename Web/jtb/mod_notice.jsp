<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
<%request.setCharacterEncoding("utf-8");%>
<%!
	String admin;
	String notice;
	String new_n;
%>
<%
	notice = "";
    admin = request.getParameter("admin");
	new_n = request.getParameter("new_notice");
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	String msg = "";
	if(request.getMethod().equalsIgnoreCase("post")){	
		Class.forName("com.mysql.jdbc.Driver");
		Connection con = DriverManager.getConnection(connectString,users, pwd);
		Statement stmt = con.createStatement();
		try{
			String sql = "update notice set notice = '" + new_n + "' , from_a = '" + admin + "' where id = 1 ";
			int cnt = stmt.executeUpdate(sql);
			if(cnt>0)msg = "成功!";
			stmt.close(); con.close();
		}catch(Exception e){
			msg = e.getMessage();
		}
		response.sendRedirect("GoodList.jsp?user=admin&admin="+admin);
	}
	else {
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			String str = "select * from notice where id = 1";
			ResultSet rs = stmt.executeQuery(str); 
			while(rs.next()) {
				notice = rs.getString("notice");
			}
			rs.close(); stmt.close(); con.close();
		}
		catch (Exception e){
			msg = e.getMessage();
		}
	}	
%>
<!DOCTYPE HTML>
<html lang="zh-cn">
	<head>
	<title>修改公告</title>
	<meta charset="utf-8">
	<style>
		.xiugai {
			margin: 0 auto;
			width:300px;
			height:340px;
			position:relative;
			top:70px;
			border:solid 2px black;
			padding:20px;
			border-radius:20px;
			z-index:3;
			background:white;
			box-shadow:inset -3px 3px 2px #AAAAAA,-3px 3px 2px #999;		
		}
		body {
			background:url(images/modify5.jpg);
			background-size:contain;	
		}
	</style>
	</head>
	<%=msg%>
	<body>
		<div class="xiugai">
			<form action="mod_notice.jsp?user=admin&admin=<%=admin%>" method="post" enctype="application/x-www-form-urlencoded">
				<span style="font-weight:bold;">公告：</span><textarea type="text" name="new_notice" style="height: 150px; width: 200px; vertical-align: top;"><%=notice%></textarea></br></br>
				<input name="submit" type="submit" value="提交" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px;margin-top: 20px; margin-left: 40px; margin-right: 30px; "></br></br>
			</form>
			<a href="GoodList.jsp?user=admin&admin=<%=admin%>"><button style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-left: 70px; position: relative; top: -43px; left: 90px; ">返回</button></a>
		</div>
	</body>
</html>
