// 调用方法
/*
	SMTP_D->send_mail(object sender, mixed email, string subject, string content);
	sender: 发信人
	email: 可以是 玩家 ID、玩家 object、登录 object 或 email 地址
	subject: 主题
	content: 内容
*/
// olives 初稿 2001-04-15@Beijing
// yuj@SJ 完美装修 2001-04-16@Toronto

#include <ansi.h>
#include <mudlib.h>
#include <net/socket.h>

#define MAIL_NAME "admin"
#define PUBLIC_MUD_MAIL "admin@mymud.com"
#define SMTP_SERVER "202.97.175.44"
#define SMTP_PORT "25"
#define SMTP_CLIENT_VERSION "LPC SMTP Client v1.0"
#define DOMAIN_NAME "mymud.com"
#define TIME_OUT 30

class email
{
	string address;	// 收件者地址
	string body;	// 内容
	int status;	// 状态码
	int time_stamp;
	object user;
}

protected void time_out(int fd, int time_stamp);
protected void success_send(int fd);
protected void mail_error(int fd, string message);

protected mapping queue = ([]);
/* smtp server domain name & ip*/
protected string smtp_server = SMTP_SERVER " " SMTP_PORT;

void create()
{
	seteuid(getuid());
}

int send_mail(object user, mixed mail, string subject, string content)
{
	string msg;
	int s,err;
	class email newmail;

	if (geteuid(previous_object()) != ROOT_UID || !objectp(user))
		return 0;

	if (!stringp(content))
	{
		tell_object(user, "邮件内容为空。\n");
		return 0;
	}

	if (stringp(mail) && strsrch(mail, "@") < 0)
	{
		string tmp = mail;

		mail = new(LOGIN_OB);
		mail->set("id", tmp);
		mail->restore();
		tmp = mail->query("email");
		destruct(mail);
		mail = tmp;
	} else if (objectp(mail))
	{
		mixed tmp;

		if (stringp(tmp = mail->query("email")))
			mail = tmp;
		else if (objectp(tmp = mail->query_temp("link_ob")))
			mail = tmp->query("email");
	}
	if (!stringp(mail) || sscanf(mail, "%*s@%*s.%*s") != 3) {
		tell_object(user, "邮件地址错误。\n");
		return 0;
	}

	mail = lower_case(mail);
	// 过滤无效结束标志
	content = replace_string(content, "\n.\n", "\n\n");
	if (!stringp(subject)) subject = CHINESE_MUD_NAME "邮件";

	msg = sprintf(
		"From: \"%s\" <%s>\n"
		"To: <%s>\n"
		"Subject: %s\n"
		"Date: %s\n"
		"X-Mailer: %s\n"
		"MIME-Version: 1.0\n\n"
		"%s\n"
		"http://www.mymud.com/",
		CHINESE_MUD_NAME, PUBLIC_MUD_MAIL,
		mail,
		subject,
		ctime(time()),
		SMTP_CLIENT_VERSION,
		content
	);
	newmail = new(class email);
	newmail->address = mail;
	newmail->body = msg;
	newmail->user = user;
	newmail->time_stamp = time();

	s = socket_create(STREAM, "read_callback", "close_callback");
	if(s<0)
	{
		tell_object(user, "创建套接字发生错误。\n");
		return 0;
	}

	queue += ([ s : newmail ]);
	err = socket_connect(s, smtp_server, "read_callback", "write_call_back");
	if (err != EESUCCESS)
	{
		tell_object(user, "连接服务器发生错误。\n");
		map_delete(queue, s);
		socket_close(s);
		return 0;
	}
	tell_object(user,"邮件发送中，请稍候。\n");
	call_out("time_out", TIME_OUT, s, newmail->time_stamp);
	return 1;
}

protected void time_out(int fd, int s)
{
	class email mailmsg;
	object usr;

	if (undefinedp(queue[fd]))
		return;

	mailmsg = queue[fd];
	if (mailmsg->time_stamp != s)
		return;

	if (objectp(usr = mailmsg->user))
		tell_object(usr, BLINK "发送过程超时，请重新再发送一次。\n" NOR);
	map_delete(queue,fd);
	socket_close(fd);
}

protected void success_send(int fd)
{
	class email mailmsg;
	object usr;

	if(undefinedp(queue[fd]))
		return;

	mailmsg = queue[fd];
	if(objectp(usr = mailmsg->user))
		tell_object(usr, sprintf(HIW "信件已经发往：%s！\n" NOR, mailmsg->address));
	map_delete(queue, fd);
	socket_close(fd);
}

protected void mail_error(int fd, string message)
{
	class email mailmsg;
	object usr;

	if(undefinedp(queue[fd]))
		return;

	mailmsg = queue[fd];

	if (objectp(usr = mailmsg->user))
	{
		tell_object(usr, sprintf(BLINK "发送过程中出现异常错误：%s\n" NOR,
			message)
		);
	}

	map_delete(queue, fd);
	socket_close(fd);
}

protected void hello(int fd, string msg)
{
	if (!undefinedp(queue[fd]))
		socket_write(fd, msg);
}

protected void read_callback(int fd, string message)
{
	int rcode;
	class email mailmsg;

	if(undefinedp(queue[fd]))
	{
		socket_close(fd);
		return;
	}

	mailmsg = queue[fd];

	rcode = atoi(message[0..2]);

	if (!rcode || (rcode >= 500))
	{
		mail_error(fd, message);
		return;
	}
	switch (mailmsg->status++) {
		case 0 :
			if (rcode == 220)
			{
				call_out("hello", 1, fd, sprintf("HELO %s\n", DOMAIN_NAME));
				return;
			}
			break;
		case 1 :
			if (rcode == 250)
			{
				socket_write(fd, sprintf("MAIL FROM: %s\n", MAIL_NAME));
				return;
			}
			break;
		case 2 :
			if (rcode == 250)
			{
				socket_write(fd, sprintf("RCPT TO: <%s> NOTIFY=NEVER\n", mailmsg->address));
				return;
			}
			break;
		case 3 :
			if (rcode == 250)
			{
				socket_write(fd, "DATA\n");
				return;
			}
			break;
		case 4 :
			if (rcode == 354)
			{
				socket_write(fd, sprintf("%s\n.\n", mailmsg->body));
				return;
			}
			break;
		case 5 :
			if (rcode != 451)
			{
				socket_write(fd, "QUIT\n");
				return;
			}
			break;
		case 6 :
			if(rcode == 221)
			{
				success_send(fd);
				return;
			}
	}
	mail_error(fd,message);
}
