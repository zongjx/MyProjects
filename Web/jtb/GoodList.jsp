<%@ page language="java" import="java.util.*,java.sql.*" contentType="text/html; charset=utf-8"%>
	<%! 
		String shuru;
		String gclass;
		String user;
		String admin;
		String notice;
	%>
	<% request.setCharacterEncoding("utf-8");
		String msg ="";
		String flag = "";
		notice = "无";
		user = "";
		admin = "";
		user = request.getParameter("user");
		admin = request.getParameter("admin");
		gclass = request.getParameter("class");
		shuru = request.getParameter("num");
		Integer pgno = 0; //当前页号
		Integer pgcnt = 3;  //每页行数
		Integer pres ;
		String param = request.getParameter("pgno");
		if(param != null && !param.isEmpty()){
			pgno = Integer.parseInt(param);
		}
		param = request.getParameter("pgcnt");
		if(param != null && !param.isEmpty()){
			pgcnt = Integer.parseInt(param);
		}
		pres = pgno*pgcnt;
		int pgprev = (pgno>0)?pgno-1:0;
		int pgnext = pgno+1;
		// 连接数据库
		String connectString = "jdbc:mysql://120.78.73.208:3306/jtb"+ "?autoReconnect=true&useUnicode=true&characterEncoding=UTF-8";
		String users="root";
		String pwd="123456";
		StringBuilder table = new StringBuilder();
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			String str;
			if(gclass.equals("")){
				str = "select * from goods where name like \"%" + shuru + "%\" limit " + pres.toString() + "," + pgcnt.toString();
			}
			else{
				if(gclass.equals("*")){
					str = "select * from goods limit " + pres.toString() + "," + pgcnt.toString();
				}
				else {
					str = "select * from goods where class = \"" + gclass +"\" limit " + pres.toString() + "," + pgcnt.toString();
				}
				
			}
			ResultSet rs = stmt.executeQuery(str); 
			table.append("<table><tr><th>商品图片</th><th>商品名称</th><th>价格</th>"+"<th> 分类 </th><th>选项</th></tr>");
			while(rs.next()) {
				flag = "1";
				if(user.equals("admin")){
					table.append(String.format(
								"<tr><td><img id=\"pic\" src=\"%s\"></td><td>%s</td><td>%s</td><td>%s</td><td>%s </td></tr>",
								rs.getString("pic"),
								rs.getString("name"),
								rs.getString("price"),
								rs.getString("class"),
								"<a class=\"linked\" href='goodDetail.jsp?user=" + user + "&id="+rs.getString("id")+"' style=\"text-decoration:none; \">查看详细信息</a> / <a class=\"linked\" href='mod_goods.jsp?user=" + user + "&id="+rs.getString("id")+"' style=\"text-decoration:none; \">修改商品信息</a>"));
				}
				else{
					table.append(String.format(
								"<tr><td><img id=\"pic\" src=\"%s\"></td><td>%s</td><td>%s</td><td>%s</td><td>%s </td></tr>",
								rs.getString("pic"),
								rs.getString("name"),
								rs.getString("price"),
								rs.getString("class"),
								"<a class=\"linked\" href='goodDetail.jsp?user=" + user + "&id="+rs.getString("id")+"' style=\"text-decoration:none; \">查看详细信息</a>"));
				}
			}
			table.append("</table>");
			rs.close(); stmt.close(); con.close();
		}
		catch (Exception e){
			msg = e.getMessage();
		}
		try{
			Class.forName("com.mysql.jdbc.Driver");
			Connection con=DriverManager.getConnection(connectString, users, pwd);
			Statement stmt=con.createStatement();
			String str;
			str = "select * from notice where id = 1";
			ResultSet rs = stmt.executeQuery(str); 
			if(rs.next()){
				notice = rs.getString("notice");
			}
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
		<title>HOME</title>
	</head>
	<style>
			body {
				background: #CC808A50;
			}
			#slideMain {            
	            width: 800px;
	            height: 400px;
	            margin: 0 auto;
	            margin-top: 130px;
	            overflow: hidden;           
	        }
	        .slide {
	            width:800px;
	        }

	        #img1 {
	        	position: relative;
	        	top: -30px;
	        	display: inline-block;
	        	animation-timing-function: linear;
	        	animation-name: myfirst;
	        	animation-duration: 10s;
	        	animation-iteration-count: infinite;
	        }

	        #img2 {
	        	position: relative;
	        	top: -537px;
	        	display: inline-block;
	        	animation-timing-function: linear;
	        	animation-name: mysecond;
	        	animation-duration: 10s;
	        	animation-iteration-count: infinite;
	        }

	        #img3 {
	        	position: relative;
	        	top: -1073px;
	        	display: inline-block;
	        	animation-timing-function: linear;
	        	animation-name: mythird;
	        	animation-duration: 10s;
	        	animation-iteration-count: infinite;
	        }

	        #img4 {
	        	position: relative;
	        	top: -1610px;
	        	left: 0px;
	        	display: inline-block;
	        	animation-timing-function: linear;
	        	animation-name: myforth;
	        	animation-duration: 10s;
	        	animation-iteration-count: infinite;
	        }

	        @keyframes myfirst { 
	            0%{transform: translate(0px,0px);}
	            23%{transform: translate(0px,0px);}
	            25%{transform: translate(-800px,0px);opacity: 1;}
	            26%{transform: translate(-800px,0px);opacity: 0;}
	            97%{transform: translate(800px,0px);opacity: 0;}
	            98%{transform: translate(800px,0px);opacity: 1;}
	            100%{transform: translate(0px,0px);}
	        }

	        @keyframes mysecond { 
	            0%{transform: translate(800px,0px);}
	            23%{transform: translate(800px,0px);}
	            25%{transform: translate(0px,0px);}
	            48%{transform: translate(0px,0px);}
	            50%{transform: translate(-800px,0px);}
	            100%{transform: translate(-800px,0px);}
	        }

	        @keyframes mythird { 
	            0%{transform: translate(800px,0px);}
	            48%{transform: translate(800px,0px);}
	            50%{transform: translate(0px,0px);}
	            73%{transform: translate(0px,0px);}
	            75%{transform: translate(-800px,0px);}
	            100%{transform: translate(-800px,0px);}
	        }

	        @keyframes myforth { 
	            0%{transform: translate(800px,0px);}
	            73%{transform: translate(800px,0px);}
	            75%{transform: translate(0px,0px);}
	            98%{transform: translate(0px,0px);}
	            100%{transform: translate(-800px,0px);}
	        }
	        #nav_outer {
				background:#FFDEAD;
	        	height:60px;
	        	width: 105%;
				position: fixed;
	        	top:0px;
				left:-5px;
				z-index: 5;
	        }
			#nav {
				height:60px;
				width:270px;
				position:fixed; 
				top:0px;
			}
	        .wrapper {
				height: 60px;
				width:auto;    
        	}
			.nav_mainbox {
				list-style-type:none;
				height:60px;
				width:135px;
				position:fixed;
				top:0;
				left:0;
			}
			.nav_mainbox:hover{
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
	        .nav_main {
				position: relative;
				top: 20px;
				left:40px;
        		font-weight: bold;
        	}
			.nav_classbox {
				list-style-type:none;
				height:60px;
				width:135px;
				position:fixed;
				top:0;
				left:135px;
			}
			.nav_classbox:hover{
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
	        .nav_class {
				position: relative;
				top: 20px;
				left:40px;
        		font-weight: bold;
        	}
        	li a {
        		text-decoration: none;
				color: SaddleBrown;
        	}
	        .wrapper>li:hover>.subnav {
	        	visibility: visible;
				opacity: 1;
	        }
	        .subnav {
				width: 135px;
				position: relative;
				top: 42px;
				left: -40px;
	        	list-style-type:none;
	        	visibility: hidden;
				opacity: 0;
				z-index:5;
	        }
			.wrapper>li:hover li{
				opacity:1;
			}
	        .subnav li {
				position:relative;
				background: rgba(230,230,230,1);
	        	padding-bottom: 13px;
				padding-top: 13px;
	        	height: 30px;   	
	        	text-align: center;
				opacity:0;
				transition-property:opacity;
				transition-duration: 0.3s;
	        }
			.subnav #li1 {
				transition-delay:0s;
				background:yellow;
			}
			.subnav #li2 {
				transition-delay:0.1s;
				background:lightgreen;
			}
			.subnav #li3 {
				transition-delay:0.2s;
				background:lightblue;
			}
			.subnav #li4 {
				transition-delay:0.3s;
				background:Deepskyblue;
			}
			.subnav #li5 {
				transition-delay:0.4s;
				background:Magenta;
			}
			.subnav #li6 {
				transition-delay:0.5s;
				background:pink;
			}
			.subnav #li1:hover {
				background: rgb(250,250,250);
			}
			.subnav #li2:hover {
				background: rgb(250,250,250);
			}
			.subnav #li3:hover {
				background: rgb(250,250,250);
			}
			.subnav #li4:hover {
				background: rgb(250,250,250);
			}
			.subnav #li5:hover {
				background: rgb(250,250,250);
			}
			.subnav #li6:hover {
				background: rgb(250,250,250);
			}
			
	        .querry {
	        	width:700px;
	        	height:60px;
	        	position: fixed;
				top:0;
				left:270px;
	        }	        
			form {
				height:60px;
				font-weight: bold;
	        	color: grey;
			}
			#search {
				width:600px;
				float:left;
				height:60px;
			}
			.search_button{
				position:relative;
				top:13px;
				left: -20px;
				width:60px; 
				height:30px; 
				float:left;
				border: solid 2px orange;
				border-radius: 5px;
				font-family:黑体;
				font-size:15px;
				font-weight:bold;
				background:orange;
			}
			.search_button:hover {
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
	        table{
				position: relative;
				top: 150px;
				width: 700px;
				left: -80px;
				background:transparent;
			}
			th,td {
				background:white; 
				border-radius:5px; 
				box-shadow: inset 3px 2px 5px #DDD;
			}
			th {
				padding: 5px;
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
			.linked:link,.linked:visited {
				color:blue;
			}
			.yonghu {
				position: fixed;
				width:280px;
				height:60px;
				top: 0px;
				left: 970px;
        		font-weight: bold;
				color:SaddleBrown;
			}
			.yonghu:hover{
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
			.yonghu:hover >.subname {
				opacity:1;
				visibility:visible;
			}
			.subname {
				background: rgba(230,230,230,1);
				position: fixed;
				width:280px;
				height:60px;
				top: 60px;
				visibility:hidden;
				opacity:0;
				transition-property:opacity;
				transition-duration: 1s;
			}
			.shangpin {
				height:60px;
				width:140px;
				float:left;
			}
			.shangpin:hover {
				background: rgba(250,250,250,1);
			}
			.guanli {
				height:60px;
				width:140px;
				float:left;
			}
			.guanli:hover {
				background: rgba(250,250,250,1);
			}
			.gerenxinxi {
				height:60px;
				width:280px;
				float:left;
			}
			.gerenxinxi:hover {
				background: rgba(250,250,250,1);
			}
			.buy {
				height:60px;
				width:100px;
				position:fixed;
				top:0px;
				left:1250px;
			}
			#buy_btn {
				position:relative;
				top:15px;
				left:25px;
				width:50px; 
				height:30px; 
				float:left;
				border: solid 2px orange;
				border-radius: 5px;
				background:orange;
			}
			#buy_btn:hover {
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
			#buy_btn1 {
				position:relative;
				top:15px;
				left:0px;
				width:90px; 
				height:30px; 
				float:left;
				border: solid 2px orange;
				border-radius: 5px;
				background:orange;
			}
			#buy_btn1:hover {
				background:linear-gradient(to bottom right,#FFCC00 20%,#FF9900 90%);
			}
			.shangpin a {
				font-weight: bold;
				color:grey;
				text-decoration:none;
			}
			.manager {
				text-decoration:none;
			}
			#main {
				height:600px;
			}
			#footer {
				font-family: "微软雅黑";
				font-weight: bold;
				vertical-align: middle;
				text-align: center;
				height: 30px;
				width: 100%;
				background:gainsboro;
				padding-top: 5px;
			}
			.nav_class:hover {
				color: RosyBrown;
			}
			
			.manager {
				font-weight:bold;
				color:black;
			}
			.manager:linked {
				color:black;
			}
			.leftad {
				position: fixed;
				left: 0px;
				width:150px;
				bottom:10px;
			}
			.rightad {
				position: fixed;
				right: 0px;
				width:150px;
				bottom:10px;
			}
			
			.notice {
				background: url("images/notice3.png"); 
				background-size: contain;
				width:260px;
				height: 165px;
				position: fixed;
				top: 150px;
				right: 0px;
			}
	</style>
	<body>
		<div id="nav_outer">
			<div id="nav">
				<ul class="wrapper" >
		            <li class="nav_mainbox"><a href="GoodList.jsp?user=<%=user%>" class="nav_main" style="font-family:黑体;">网站首页</a></li>
                    <li class="nav_classbox"><a href="GoodList.jsp?user=<%=user%>&class=*" class="nav_class" style="font-family:黑体;">所有分类</a>
                    	<ul class="subnav"> 
                    		<li id="li1"><a href="GoodList.jsp?user=<%=user%>&class=服装饰品" class="item" style="font-family:黑体;">服装饰品</a></li>
		                    <li id="li2"><a href="GoodList.jsp?user=<%=user%>&class=童装玩具" class="item" style="font-family:黑体;">童装玩具</a></li>
		                    <li id="li3"><a href="GoodList.jsp?user=<%=user%>&class=生活百货" class="item" style="font-family:黑体;">生活百货</a></li>
		                    <li id="li4"><a href="GoodList.jsp?user=<%=user%>&class=运动户外" class="item" style="font-family:黑体;">运动户外</a></li>
		                    <li id="li5"><a href="GoodList.jsp?user=<%=user%>&class=数码优品" class="item" style="font-family:黑体;">数码优品</a></li>
		                    <li id="li6"><a href="GoodList.jsp?user=<%=user%>&class=文教乐器" class="item" style="font-family:黑体;">文教乐器</a></li>
                    	</ul>	                    
                    </li>
               </ul>
			</div> 
			<div class="querry">
				<form action="GoodList.jsp?user=<%=user%>&class="  method="post" name="que">
					<div id="search">
						<div style="height:20px; width:80px; position:relative; left:30px; padding: 20px 40px; float:left; font-family:黑体; color:SaddleBrown;">搜索商品:</div>
						<div style="height:50px; width: 420px; position:relative; top:7px; float:left; padding:5px 0px;"><input id="num" name="num" type="text" style="height:30px; width:410px; font-size: 15px; font-weight:bold;" placeholder="请输入搜索关键字"></div>
					</div>
					<input type="submit" name="sub" value=" 搜索 " class="search_button">
				</form>
			</div>
			<div class="yonghu">
				<div style="width: 200px; margin:0 auto; position:relative; top:20px; text-align:center;">
					<%if(user.equals("admin")){%>
					<span style="font-family:黑体; ">管理员: </span>
					<%}else{%>
					<span style="font-family:黑体;">用户: </span>
					<%}%>
				<span class="manager"><%=user%></span>
				</div>
				<div class="subname">
					<%if(user.equals("admin")){%>
					<div class="shangpin">
						<span style="position:relative; top:20px; left:40px;"><a href="add.jsp?user=<%=user%>&admin=<%=admin%>" class="GOOD" style="font-family:黑体; color:black;">新增商品</a></span>
					</div>
					<div class="guanli">
						<span style="position:relative; top:20px; left:20px;"><a href="manager.jsp" class="manager" style="font-family:黑体;">管理所有账号</a>	</span>
					</div>
					<%}else{%>
					<div class="gerenxinxi">
						<span style="position:relative; top:20px; left:90px;"><a href="modify.jsp?user=<%=user%>" class="manager" style="font-family:黑体;">修改个人信息</a></span>
					</div>
					<%}%>
				</div>
			</div>
			<%if(user.equals("admin")){%>
			<div class="buy">
				<a href="trade.jsp?admin=<%=admin%>&user=<%=user%>"><button id="buy_btn1">交易记录</button></a>
			</div>
			<%}else{%>
			<div class="buy">
				<a href="shop.jsp?user=<%=user%>"><button id="buy_btn"><img src="images/cart.png" style="height:20px;width:18px;"></button></a>
			</div>
			<%}%>
			
		
			
    	</div>
		
		<div id="main">
			<%if(shuru == null && gclass == null){%>
				<div id="slideMain">
					<div class="slides">
						 <img class="slide" id="img1" src="images/img1.jpg">
						 <img class="slide" id="img2" src="images/img2.jpg">
						 <img class="slide" id="img3" src="images/img3.jpg">
						 <img class="slide" id="img4" src="images/img4.jpg">
					</div>
				</div> 
			<%}else{%>
				<div class="container">	
					<%=table%>
					<br/><br/>
					<div style="float:right; position:relative; top:150px;">
						<%if(pgno != 0){%>
						<a href="GoodList.jsp?user=<%=user%>&pgno=<%=pgprev%>&pgcnt=<%=pgcnt%>&num=<%=shuru%>&class=<%=gclass%>">上一页</a>
						<%}%>
						&nbsp
						<%if(flag.equals("1")){%>
						<a href="GoodList.jsp?user=<%=user%>&pgno=<%=pgnext%>&pgcnt=<%=pgcnt%>&num=<%=shuru%>&class=<%=gclass%>">下一页</a>
						<%}%>
					</div>
					<br><br>
					<%=msg%><br><br>
				</div>
			<%}%>
		</div>
		
		<div class="notice">
			<p><span style="font-weight:bold; position: relative; left:115px; top:20px;">公告</span></p>
			<p style="width:210px;word-wrap:break-word; word-break:break-all; position: relative; left: 30px; top:5px; font-size:10px;"><%=notice%></p>
			<%if(user.equals("admin")){%>
				<a href="mod_notice.jsp?user=admin&admin=<%=admin%>" style="position: relative; left: 30px;;">修改公告</a>
			<%}%>
		</div>
		
	</body>
	
	<footer>
		<div id="footer">
			Copyright &copy2017-2018 JTB Software Foundation. All Rights Reserved
		</div>
	</footer>

</html>

	
