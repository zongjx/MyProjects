<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
<%request.setCharacterEncoding("utf-8");%>
<%!
	String user;
	String sex;
	String addr;
	String info;
	String manager;
%>
<%
	user = request.getParameter("user");
	manager="";
	manager = request.getParameter("manager");
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	String msg = "";
	sex="";
	addr="";
	info="";
	if(request.getMethod().equalsIgnoreCase("post")){	
		if(request.getParameter("delete").equals("true")){
			Class.forName("com.mysql.jdbc.Driver");
			Connection con = DriverManager.getConnection(connectString,users, pwd);
			Statement stmt = con.createStatement();
			try{
				String sql = "delete from user where name ='" + user + "';";
				int cnt = stmt.executeUpdate(sql);
				if(cnt>0)msg = "删除成功!";
				stmt.close();
			}catch(Exception e){
				msg = e.getMessage();
			}
			try{
				String sql = "delete from buy where user ='" + user + "';";
				Statement stmt1 = con.createStatement();
				int cnt = stmt1.executeUpdate(sql);
				if(cnt>0)msg = "删除成功!";
				stmt1.close(); con.close();
			}catch(Exception e){
				msg = e.getMessage();
			}
			if(manager.equals("manager")){
				response.sendRedirect("manager.jsp");
			}
			else{
				response.sendRedirect("index.jsp");
			}
			
		}
		else {
			try{
				Class.forName("com.mysql.jdbc.Driver");
				Connection con=DriverManager.getConnection(connectString, users, pwd);
				Statement stmt=con.createStatement();
				String sql = "update user set password = '" 
				+ request.getParameter("pass") +"',sex = '" 
				+ request.getParameter("sex") +"',addr = '" 
				+ request.getParameter("addr") +"',info = '" 
				+ request.getParameter("info") + "' where name = '" 
				+ user + "';" ;
				int cnt = stmt.executeUpdate(sql);
				if(cnt>0)msg = "修改成功!";
				stmt.close(); con.close();
				if(manager.equals("manager")){
					response.sendRedirect("GoodList.jsp?user=admin");
				}
				else{
					response.sendRedirect("GoodList.jsp?user="+user);
				}
			}catch(Exception e){
				msg = e.getMessage();
			}			
		}
	}
	else {
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			String str = "select * from user where name = \"" + user +"\"";
			ResultSet rs = stmt.executeQuery(str); 
			while(rs.next()) {
				sex = rs.getString("sex");
				addr = rs.getString("addr");
				info = rs.getString("info");
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
	<title>修改用户信息</title>
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
	<body>
		<div class="xiugai">
			<form action="modify.jsp?delete=false&user=<%=user%>&manager=<%=manager%>" method="post" enctype="application/x-www-form-urlencoded">
				<span style="font-weight:bold;">用户名：</span>&nbsp&nbsp<%=user%></br></br>
				<span style="font-weight:bold;">密码：</span>&nbsp&nbsp&nbsp&nbsp<input type="password" name="pass" style="width: 200px;"></br></br>
				<span style="font-weight:bold;">性别：</span>&nbsp&nbsp&nbsp <input type="radio" name="sex" value="男" <%=sex.equals("男")?"checked":""%>>男&nbsp&nbsp&nbsp
									  <input type="radio" name="sex" value="女" <%=sex.equals("女")?"checked":""%>>女&nbsp&nbsp&nbsp
									  <input type="radio" name="sex" value="保密" <%=sex.equals("保密")?"checked":""%>>保密</br></br>
				<span style="font-weight:bold;">地址：</span>&nbsp&nbsp&nbsp&nbsp<input type="text" name="addr" style="width: 200px;" value="<%=addr%>"></br></br>
				<span style="font-weight:bold;">个人信息：</span><textarea type="text" name="info" style="height: 50px; width: 200px; vertical-align: top;"><%=info%></textarea></br></br>
				<input name="submit" type="submit" value="提交" style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px;margin-top: 20px; margin-left: 40px; margin-right: 30px; "></br></br>
			</form>
			<a href="GoodList.jsp?user=<%=user%>"><button style="height: 25px; width: 80px; border: solid 1px #000; border-radius: 3px; margin-left: 70px; position: relative; top: -43px; left: 90px; ">返回</button></a>
			<form action="modify.jsp?delete=true&user=<%=user%>&manager=<%=manager%>" method="post" enctype="application/x-www-form-urlencoded">
				<input name="submit" type="submit" value="注销用户" style="height: 25px; width: 80px; border: solid 3px #FF0000; border-radius: 3px; background:linear-gradient(to bottom right,red 5%,Salmon 80%);position: relative; top:-8px; left: 100px; color:white;"></br></br>
			</form>
		</div>
	</body>
</html>
