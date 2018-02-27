<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
<%request.setCharacterEncoding("utf-8");%>
<%
	String isExist;
	String isNotCon;
	isNotCon = "";
	isExist = "";
	String msg ="";
	String name = request.getParameter("user");
	String pass = request.getParameter("pass");
	String conpass = request.getParameter("conpass");
	String sex = request.getParameter("sex");
	String addr = request.getParameter("addr");
	String info = request.getParameter("info");
	if(pass.equals(conpass)&&!pass.equals("")){
		String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"
						+ "?autoReconnect=true&useUnicode=true"
						+ "&characterEncoding=UTF-8"; 
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, "root", "123456");
			Statement stmt=con.createStatement();
			ResultSet rs=stmt.executeQuery("select * from user");
			while(rs.next()) {
				if(rs.getString("name").equals(name)){
					isExist = "1";
					break;
				}
			}
			rs.close();
			stmt.close();
			con.close();
		}
		catch (Exception e){
		  msg = e.getMessage();
		}
		if(isExist.equals("")){
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, "root", "123456");
			Statement stmt = con.createStatement();
			try{
				String fmt="insert into user(name,password,sex,info,addr) values('%s', '%s', '%s', '%s', '%s');";
				String sql = String.format(fmt,name,pass,sex,info,addr);
				int cnt = stmt.executeUpdate(sql);
				if(cnt>0)msg = "保存成功!";
				stmt.close(); 
				con.close();
			}catch(Exception e){
				msg = e.getMessage();
			}
		}
		if(isExist.equals("")){
			response.sendRedirect("GoodList.jsp?user="+name);
		}
	}
	else{
		isNotCon = "1";
	}
%>
<html>
	<head>
		<meta charset="utf-8">
		<%if(isNotCon.equals("1")){%>
		<%if(pass.equals("")){%>
		<title>密码不能为空！</title>
		<%}else{%>
		<title>密码不一致！</title>
		<%}}if(isExist.equals("1")){%>
		<title>用户名已存在！</title>
		<%}%>
	</head>
	<form action="index.jsp" method="post" enctype="application/x-www-form-urlencoded">
		<%if(isNotCon.equals("1")){%>
		<%if(pass.equals("")){%>
		<div style="font-size:3em; margin: 0 auto; width: 600px; text-align: center; position: relative; top: 300px;">密码不能为空！</div><br/><br/>
		<%}else{%>
		<div style="font-size:3em; margin: 0 auto; width: 600px; text-align: center; position: relative; top: 300px;">密码不一致！</div><br/><br/>
		<%}}if(isExist.equals("1")){%>
		<div style="font-size:3em; margin: 0 auto; width: 600px; text-align: center; position: relative; top: 300px;">用户名已存在！</div><br/><br/>
		<%}%>
		<div style="width: 100px; margin:0 auto;position: relative; top: 300px;"><input name="back" type="submit" value="返回"></div>
	</form>
</html>