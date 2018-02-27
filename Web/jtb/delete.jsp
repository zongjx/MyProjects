<%@ page language="java" import="java.util.*,java.sql.*"
	contentType="text/html; charset=utf-8"%>
	<%! 
		String id;
		String user;
		String dtype;
		String id2;
	%>
	<% request.setCharacterEncoding("utf-8");
	String msg = "";
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root"; String pwd="123456";
	
	user = request.getParameter("user");
	dtype = request.getParameter("dtype");
	id = request.getParameter("pid");
	id2 = request.getParameter("id");
	Class.forName("com.mysql.jdbc.Driver");
	Connection con = DriverManager.getConnection(connectString,users, pwd);
	Statement stmt = con.createStatement();
	if(dtype.equals("user")){
		try{ 
			String sql=" DELETE from user WHERE id="+  id +";"  ;
			int cnt = stmt.executeUpdate(sql);
			if(cnt>0)msg = "Delete Success!";
			stmt.close();
			
		}catch (Exception e){
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
		response.sendRedirect("manager.jsp");
	}
	else if(dtype.equals("buy")){
		try{ 
			String sql=" delete from buy WHERE id = "+ id2 +";"  ;
			int cnt = stmt.executeUpdate(sql);
			if(cnt>0)msg = "Delete Success!";
			stmt.close();
			con.close();
		}catch (Exception e){
			msg = e.getMessage();
		}
		response.sendRedirect("shop.jsp?user=" + user);
	}
	%>
<!DOCTYPE HTML>
<html>
	<head>
		<title>删除记录</title>
	</head>
	<body>
	</body>
</html>