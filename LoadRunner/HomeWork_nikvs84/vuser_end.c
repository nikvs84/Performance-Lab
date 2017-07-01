vuser_end()
{
	lr_think_time(10);
	
	lr_start_transaction("Forum_WEB_07_logout");

	web_url("Log out [ nikvs84 ]", 
		"URL=http://u0351361.isp.regruhosting.ru/login.php?logout=true&sid={ssid}", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://u0351361.isp.regruhosting.ru/viewtopic.php?p=210", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Forum_WEB_07_logout",LR_AUTO);
	
	return 0;
}
