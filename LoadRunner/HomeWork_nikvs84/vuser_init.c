vuser_init()
{
	web_reg_save_param_regexp (
	    "ParamName=ssid",
	    "RegExp=phpbb2mysql_sid=(.+);",
//	    "Ordinal=All",
//	SEARCH_FILTERS,
//	    "RequestUrl=*/files/index.html",
	LAST );
	
	web_url("index.php", 
		"URL=http://u0351361.isp.regruhosting.ru/index.php", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/templates/subSilver/images/cellpic3.gif", ENDITEM, 
		"Url=/templates/subSilver/images/cellpic1.gif", ENDITEM, 
		"Url=/templates/subSilver/images/cellpic2.jpg", ENDITEM, 
		"Url=/favicon.ico", "Referer=", ENDITEM, 
		"Url=http://www.bing.com/favicon.ico", "Referer=", ENDITEM, 
		LAST);

	web_set_sockets_option("SSL_VERSION", "2&3");

	lr_start_transaction("Forum_WEB_01_login");

	web_url("login.php", 
		"URL=http://u0351361.isp.regruhosting.ru/login.php?sid={ssid}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/index.php", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/favicon.ico", "Referer=", ENDITEM, 
		LAST);
	
	web_reg_save_param_regexp (
	    "ParamName=category_link",
	    "RegExp=href=\"(.+)\" class=\"forumlink\">{category_name}</a>",
//	    "Ordinal=All",
//	SEARCH_FILTERS,
//	    "RequestUrl=*/files/index.html",
	LAST );	

	web_submit_data("login.php_2", 
		"Action=http://u0351361.isp.regruhosting.ru/login.php", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/login.php?sid={ssid}", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={user_name}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=redirect", "Value=", ENDITEM, 
		"Name=login", "Value=Log in", ENDITEM, 
		LAST);

	lr_end_transaction("Forum_WEB_01_login",LR_AUTO);	
	
	lr_think_time(10);
	
	lr_start_transaction("Forum_WEB_02_select_category");
	
	web_reg_save_param_regexp (
	    "ParamName=topic",
	    "RegExp=<a href=\"(.+)\" class=\"topictitle\">{topic_name}</a>",
//	    "Ordinal=All",
//	SEARCH_FILTERS,
//	    "RequestUrl=*/files/index.html",
	LAST );

	web_url("{category_name}", 
		"URL=http://u0351361.isp.regruhosting.ru/{category_link}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/index.php?sid={ssid}", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Forum_WEB_02_select_category",LR_AUTO);

	lr_think_time(10);
	
	return 0;
}
