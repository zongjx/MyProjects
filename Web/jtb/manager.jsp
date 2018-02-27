<%@ page language="java" import="java.util.*,java.sql.*"
	contentType="text/html; charset=utf-8"%>
<% request.setCharacterEncoding("utf-8");
	String flag = "";
	String msg ="";
	Integer pgno = 0; //当前页号
	Integer pgcnt = 5;  //每页行数
	String param = request.getParameter("pgno");
	if(param != null && !param.isEmpty()){
		pgno = Integer.parseInt(param);
	}
	param = request.getParameter("pgcnt");
	if(param != null && !param.isEmpty()){
		pgcnt = Integer.parseInt(param);
	}
	int pgprev = (pgno>0)?pgno-1:0;
	int pgnext = pgno+1;
	String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
	String users="root";
	String pwd="123456";
	StringBuilder table = new StringBuilder();
	try{
		Class.forName("com.mysql.jdbc.Driver");
		Connection con=DriverManager.getConnection(connectString, users, pwd);
		Statement stmt=con.createStatement();
		String sql=String.format("select * from user limit %d,%d",pgno*pgcnt,pgcnt);
		ResultSet rs=stmt.executeQuery(sql);
		rs.next();
		table.append("<table border=\"1\"><tr><th>id</th><th>姓名</th><th>密码</th><th>性别</th><th>个人信息</th><th>地址</th>"+"<th>操作</th></tr>");
		while(rs.next()) {
			flag = "1";
			table.append(String.format(
								"<tr><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s</td><td>%s %s</td></tr>",
								rs.getString("id"),
								rs.getString("name"),
								rs.getString("password"),
								rs.getString("sex"),
								rs.getString("info"),
								rs.getString("addr"),
								"<a href='modify.jsp?user="+rs.getString("name")+"&manager=true'" + "id=\"delete\">修改</a>",
								"<a href='delete.jsp?pid="+rs.getString("id")+"&user=" + rs.getString("name") + "&dtype=user' id=\"delete\">删除</a>"
								)
			);
		}
		table.append("</table>");
		rs.close(); stmt.close(); con.close();
	}
	catch (Exception e){
			msg = e.getMessage();
	}
%>
	
<!DOCTYPE HTML>
	<html>
		<head>
			<title>管理员界面</title>
			<style>
				body {
					background:url(images/bk6.jpg);
				}
				table{
					width: 500px;
				}
				td,th{
					border: solid grey 1px;
					margin: 0 0 0 0;
					padding: 5px 5px 5px 5px
				}
				a:link,a:visited {
					color:blue
				}
				.container{
					margin:0 auto;
					width:500px;
					text-align:center;
				}
				.message {
					margin:0 auto;
					width:550px;
					margin-top:60px;
					margin-bottom:30px;
					color:#F08080;
					font-weight:bold;
					font-size:18px;
				}
				.exit {
					position:relative;
					left:880px;
					margin-bottom:30px;
					border:solid 1px black;
					background:rgba(255,255,255,0.8);
					width:35px;
					border-radius:6px;
					padding:3px;
					box-shadow:-2px 2px 2px #999;
				}
				a {
					text-decoration:none;
				}
				#exit {
					color:black;
					font-weight:bold;
				}
				.exit:active {
					box-shadow:inset -2px 2px 2px #999;				
				}
				#delete {
					color:#B22222;
					font-weight:bold;
				}
			</style>
		</head>
	<body>
		<div class="message">
			当前是管理员身份，可查看/修改用户信息或删除非法用户。
		</div>
		<div class="exit">
			<a href="GoodList.jsp?user=admin" id="exit">返回</a>
		</div>
		<div class="container">
			<%=table%>
			<br><br>
			<div style="float:right">
			<%if(pgno != 0){%>
			<a href="manager.jsp?pgno=<%=pgprev%>&pgcnt=<%=pgcnt%>" id="last">上一页</a>
			<%}%>
			&nbsp
			<%if(flag.equals("1")){%>
			<a href="manager.jsp?pgno=<%=pgnext%>&pgcnt=<%=pgcnt%>" id="last">下一页</a>
			<%}%>
		</div>
		<br><br>
		<%=msg%><br><br>
		</div>
	</body>
</html>