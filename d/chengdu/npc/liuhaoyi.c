// NPC: /d/chengdu/npc/liuhaoyi.c
// By Jpei

inherit NPC;

#define	BOOKNUM		4
#define	SHELFNUM	7
#define	RETRY		7

int ask_question();
int ask_rule();
int do_guess(string arg);
int do_list(string arg);

void create()
{
	set_name("刘好弈", ({ "liu haoyi", "liu" }));
	set("nickname", "世袭子爵");

	set("gender", "男性");
	set("age", 40);
	set("long", "他目光炯炯，步履稳重，显是武功不低。\n");
	set_skill("unarmed", 20);
	set_skill("dodge", 15);
	set_temp("apply/damage", 5);

	set("combat_exp", 5000);
	set("attitude", "peaceful");
	
	set("inquiry", ([
		"name": "哎呀！我一个堂堂世袭子爵，居然还有人不知道我的名字？",
		"rumors": "我这里有许多失传的棋谱，好比王积薪遇狐仙婆媳的对局等，就是不知道你懂不懂围棋。",
		"here": "这里是我的家，想当年祖上蒙圣恩封了个子爵，还造了这个敕建子爵府。",
		"寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"题" : (: ask_question :),
		"question" : (: ask_question :),
		"规则" : (: ask_rule :),
		"rule" : (: ask_rule :),
	]) );

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_guess", ({"guess", "cai"}));
        add_action("do_list", ({"list", "lie"}));
	::init();
}

int ask_question()
{
	object me = this_player();
	int i, j, temp;
	string tempstr, result = "";

	if (me->query_temp("qipu_guess_win"))
		write("刘好弈笑道：“还想再解一次？好吧，等我准备好就来猜吧。”\n");
	else
		write("刘好弈道：“题目是这样的：我有一套" + CHINESE_D->chinese_number(BOOKNUM) + "册《梅花谱》，而书房里有" + CHINESE_D->chinese_number(SHELFNUM) + "个书架，现在我把这" + CHINESE_D->chinese_number(BOOKNUM) + "册书分别放到不同的书架上去，你只需猜出来每册书放在那个书架上即可。”\n");
	write("刘好弈匆匆走进书房，不一会又出来了。\n");
	write("刘好弈点点头道：“好了，来猜(guess)吧，也可以先问我规则(rule)。”\n");
	for (i = 0; i < BOOKNUM; i++) {
		temp = random(SHELFNUM) + 1;
		tempstr = "" + temp;
		for (j = 0; j < i; j++) {
			if (tempstr == result[j..j]) {
				temp = random(SHELFNUM) + 1;
				tempstr = "" + temp;
				j = -1;
			}
		}
		result += tempstr;
	}
	me->delete_temp("qipu_guess");
	me->set_temp("qipu_guess/result", result);
	return 1;
}

int ask_rule()
{
	write("刘好弈道：“规则很简单，你每次用guess来猜你认为的结果。”\n");
	write("刘好弈道：“例如，你认为第一册在２号架上，二册在１号，三册在７号，四册在５号，那就guess 2175。”\n");
	write("刘好弈道：“我会告诉你全对（指猜对了哪个书架放了哪册的）和书架对（指只猜对哪个书架放书而没有猜对放的是哪册的）的个数。”\n");
	write("刘好弈道：“上面的例子里，如果我放的顺序是一册在１号架上，二册在５号，三册在７号，四册在４号，那么答案应该是1574。”\n");
	write("刘好弈道：“你猜对７号架上是三册，表示你有一个全对，另外你猜对１号和５号架上有书，但是没猜对是哪册，表示你有二个书架对。”\n");
	write("刘好弈道：“明白了吧？可以了就开始猜(guess)吧。”\n");
	write("刘好弈道：“记住你有" + CHINESE_D->chinese_number(RETRY) + "次机会。如果你忘了你以前猜的结果，随时可以用list来查看的。”\n");
	return 1;
}

string justify_result(string result, string guess)
{
    int i, j, very_right = 0, right = 0;

	for (i = 0; i < BOOKNUM; i++) {
		for (j = 0; j < BOOKNUM; j++) {
			if (guess[i..i] == result[j..j]) {
				if (i == j) very_right++;
				else right++;
			}
		}
	}
	return "全对的有" + CHINESE_D->chinese_number(very_right) + "个，只有书架对的有" + CHINESE_D->chinese_number(right) + "个。\n";
}

int do_guess(string arg)
{
	object me = this_player();
	int i, j, times;
	string result, tempstr1, tempstr2;

	if (!(result = me->query_temp("qipu_guess/result"))) return 0;
	if (!arg) return notify_fail("你要猜什么样的结果？\n");
	if (strlen(arg) != BOOKNUM) return notify_fail("不是告诉你只有" + CHINESE_D->chinese_number(BOOKNUM) + "册书吗？\n");
	for (i = 1; i < BOOKNUM; i++)
		for (j = 0; j < i; j++)
			if (arg[i..i] == arg[j..j])
				return notify_fail("不是告诉你每册书都放在不同的书架上了吗？！\n");
	me->add_temp("qipu_guess/times", 1);
	times = me->query_temp("qipu_guess/times");
	if (arg == result) {
		if (times < 5) {
			tempstr1 = "刘好弈看着你，惊讶地道：“佩服！你只用了";
			tempstr2 = "就";
		}
		else if (times < RETRY) {
			tempstr1 = "刘好弈点头道：“不错，你只用了";
			tempstr2 = "就";
		}
		else {
			tempstr1 = "刘好弈道：“你很侥幸呀，用完了";
			tempstr2 = "才";
		}
		write(tempstr1 + CHINESE_D->chinese_number(times) + "次机会" + tempstr2 + "猜出来了。”\n");
		me->delete_temp("qipu_guess");
		me->set_temp("qipu_guess_win", 1);
		write("刘好弈在墙上按了几下，道：“好了，你可以进书房去了。”\n");
	}
	else {
		write("刘好弈道：“你猜的是" + arg + "，" + justify_result(result, arg));
		if (times < RETRY) {
			write("刘好弈道：“你还有" + CHINESE_D->chinese_number(RETRY - times) + "次机会！”\n");
			me->set_temp("qipu_guess/guess" + times, arg);
		}
		else {
			write("刘好弈生气地说：“你可真笨！" + CHINESE_D->chinese_number(RETRY) + "次机会都没猜中！答案应该是" + result + "。”\n");
			write("刘好弈道：“下次再猜吧！”\n");
			me->delete_temp("qipu_guess");
		}
	}
	return 1;
}

int do_list(string arg)
{
	object me = this_player();
	int i, times;
	string result;

	if (!(result = me->query_temp("qipu_guess/result"))) return 0;
	times = me->query_temp("qipu_guess/times");
	write("刘好弈道：“你以前猜的结果如下：”\n");
	for (i = 1; i <= times; i++) {
		write("第" + CHINESE_D->chinese_number(i) + "次：猜" + me->query_temp("qipu_guess/guess" + i) + "，" + justify_result(result, me->query_temp("qipu_guess/guess" + i)));
	}
	return 1;
}

