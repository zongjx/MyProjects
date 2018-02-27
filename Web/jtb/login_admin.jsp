<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
<%request.setCharacterEncoding("utf-8");%>
<%
	String isMatch;
	isMatch = "";
	String msg ="";
	String name = request.getParameter("user");
	String pass = request.getParameter("pass");
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"
					+ "?autoReconnect=true&useUnicode=true"
					+ "&characterEncoding=UTF-8"; 
	try{
		Class.forName("com.mysql.jdbc.Driver");
	    Connection con=DriverManager.getConnection(connectString, "root", "123456");
	    Statement stmt=con.createStatement();
	    ResultSet rs=stmt.executeQuery("select * from admin");
	    while(rs.next()) {
			if(rs.getString("name").equals(name) && rs.getString("password").equals(pass)){
				response.sendRedirect("GoodList.jsp?user=admin&admin="+name);
			}
		}
		rs.close();
		stmt.close();
		con.close();
	}
	catch (Exception e){
	  msg = e.getMessage();
	}
%>
<!DOCTYPE html>
<html>
	<head>
		<meta charset="utf-8">
		<title>密码错误！</title>
	</head>
	<form action="index.jsp" method="post" enctype="application/x-www-form-urlencoded">
		<div style="font-size:3em; margin: 0 auto; width: 600px; text-align: center; position: relative; top: 300px;">密码错误！</div><br/><br/>
		<div style="width: 100px; margin:0 auto;position: relative; top: 300px;"><input name="back" type="submit" value="返回"></div>
	</form>
</html>