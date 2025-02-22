// jiubao.c

inherit NPC;

void create()
{
	set_name("酒保", ({ "jiu bao", "jiubao", "jiu", "bao", "waiter" }) );
	set("gender", "男性" );
	set("age", 22);
	set("long",
		"这位酒保正跑前跑后地忙着。\n");
	set("combat_exp", 2000);
	set("attitude", "friendly");
	set("inquiry", ([
		"name" : "不敢不敢，小的叫韩桥声，是在本地上长大的。",
		"rumors" : "今天扬州的私盐贩子好象都跑到那边的鸣玉坊了，不知道要寻谁的晦气。",
		"here" : "这里是扬州呀，客官您竟然不知道？",
		"桃花岛": "是东海上的小岛，往杭州的东南走，到海边看能不能雇船吧？",
		"寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
		"生意" : "这里地处瘦西湖边，生意好得很。",
		"扬州" : "这里就是扬州呀，客官您这不是骑着毛驴找毛驴吗？",
		"苏州" : "在扬州的东南边，出扬州东门去找。",
		"杭州" : "在苏州的东南边。",
		"襄阳" : "从扬州往西走就能走到。",
		"成都" : "从襄阳往西再转西南。",
		"少林" : "在河南少室山，从扬州往北可以走到。",
		"少林寺" : "在河南少室山，从扬州往北可以走到。",
		"少林派" : "在河南少室山，从扬州往北可以走到。",
		"武当" : "在湖北境内，出了扬州往南面走吧。",
		"武当山" : "在湖北境内，出了扬州往南面走吧。",
		"武当派" : "在湖北境内，出了扬州往南面走吧。",
		"星宿" : "在天山西边，从扬州往西去找。",
		"星宿海" : "在天山西边，从扬州往西去找。",
		"星宿派" : "在天山西边，从扬州往西去找。",
		"明教" : "在昆仑山东边，从扬州往西走。",
		"光明顶" : "在昆仑山东边，从扬州往西走。",
		"慕容" : "在姑苏燕子圬，去苏州找找看吧。",
		"姑苏慕容" : "在姑苏燕子圬，去苏州找找看吧。",
		"归云庄" : "在太湖边上，从苏州往南走。",
		"丐帮" : "这可是个秘密呀。",
		"昆仑" : "在遥远的西域，一直往西走吧。",
		"昆仑山" : "在遥远的西域，一直往西走吧。",
		"昆仑派" : "在遥远的西域，一直往西走吧。",
		"古墓" : "在终南山，从扬州向北再折向西南吧。",
		"终南山" : "从扬州向北再折向西南吧。",
		"大理" : "在大宋的南边，所以要从扬州往南走。",
		"华山" : "在陕西境内，从扬州城西向北走可以到达。",
                "猴爪山" : "在川湘交界处，从扬州向南再向西行。",
                "铁掌山" : "在川湘交界处，从扬州向南再向西行。",
                "铁掌帮" : "在川湘交界处，从扬州向南再向西行。",
		"峨嵋山" : "在川西，从成都南门往偏西走。",
		"峨嵋派" : "在川西，从成都南门往偏西走。",
		"峨嵋" : "在川西，从成都南门往偏西走。",
	]) );
	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void init()
{	
	object ob;

	::init();
	if (base_name(environment()) != query("startroom")) return;
	if( interactive(ob = this_player()) && visible(ob) && !is_fighting() ) {
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}
}

int accept_object(object who, object ob)
{
	object zhanggui;

	if (ob->query("money_id")) {
		if (!objectp(zhanggui = present("zhang gui"))) {
			zhanggui = unew(__DIR__"zhanggui");
			if (zhanggui) zhanggui->move(environment());
		}
		if (zhanggui) {
			tell_object(who, "酒保道：“我带你去掌柜那里付帐。”\n");
			tell_object(who, "你跟着酒保来到柜台前，把钱交给掌柜。\n");
			return zhanggui->accept_object(who, ob);
		}
	}
	return 0;
}

void kill_ob(object ob)
{
	ob->remove_killer(this_object());
	remove_killer(ob);
	message_vision("酒保对$N冷笑道：“别装腔作势啦，象你这种扮凶巴巴妄图吃饭不付钱的家伙我见多了，省省吧。”\n", ob);
	message_vision("$N心中纳闷：“我这番龌龊心思怎么全被他说中了？”\n", ob);
}

void greeting(object ob)
{
	if (!present(ob, environment())) return;
	say( "酒保笑咪咪地说道：这位" + RANK_D->query_respect(ob) + "，快进来坐。\n");
}

void unconcious()
{
	say( "酒保大喊一声：“我不行了，快来接班！”\n");
	say( "结果从柜台后面又钻出一个酒保来，说：“没问题，交给我吧。”\n");
	say( "前一个酒保快快乐乐地离开了。\n");
	reincarnate();
	set("eff_qi", query("max_qi"));
	set("qi", query("max_qi"));
	set("eff_jing", query("max_jing"));
	set("jing", query("max_jing"));
	set("jingli", query("eff_jingli"));
}

void die()
{
	unconcious();
}

void relay_emote(object me,string arg)
{
	command(arg+" "+me->query("id"));
}
