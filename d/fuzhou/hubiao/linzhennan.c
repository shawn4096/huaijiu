// linzhennan.c 林震南
// modified by XiaoYao 98/12/16

#include <ansi.h>

inherit NPC;

int ask_fuwei();
int ask_yuantu();
int ask_pixie();
int ask_tong();
int test_dart();
int checkvaild(object ob);

void create()
{
	set_name("林震南", ({ "lin zhennan", "lin", "zhennan" }));
	set("gender", "男性");
	set("age", 45);
	set("long", "他就是「福威镖局」的总镖头－－林震南。\n");

	set("combat_exp", 30000);
	set("shen_type", 1);

	set("max_neili", 500);
	set("jiali", 10);
	set("no_get","林震南对你来说太重了。\n");

	set_skill("force", 40);
	set_skill("sword", 50);
	set_skill("unarmed", 50);
	set_skill("dodge", 50);
	set_skill("parry", 50);

	set("inquiry", ([
		"向阳老宅" : "那是我从前在福建时住的家院，已经破败了。",
		"福威镖局" : (: ask_fuwei :),
		"远图公" : (: ask_yuantu :),
		"林远图" : "哼！小孩子这么没礼貌，直呼先人名讳！",
		"辟邪剑法" : (: ask_pixie:),
		"铜钱" : (: ask_tong:),
		"铜板" : (: ask_tong:),
		"押镖" : (: test_dart :),
		"护镖" : (: test_dart :),
	]) );

	set("chat_chance", 2);
	set("chat_msg", ({
		"林震南说道：这个月镖局生意不错！\n",
	}) );
	set_temp("apply/attack", 50);
	set_temp("apply/defense", 50);
	set_temp("apply/damage", 15);

	setup();
	carry_object("/clone/weapon/changjian")->wield();
}

int ask_fuwei()
{
	say(
		"林震南炫耀地说：我们林家三代走镖，一来仗着先祖远图公当年闯下的威名，二\n"
		"来靠著我们林家家传的玩艺儿不算含糊，这才有今日的局面，成为大江以南首屈\n"
		"一指的大镖局。江湖上提到『福威镖局』四字，谁都要翘起大拇指，说一声：『\n"
		"好福气！好威风！』哈哈，哈哈！\n"
	);
	this_player()->set_temp("marks/林1", 1);
	return 1;
}

int ask_yuantu()
{
	if (this_player()->query_temp("marks/林1")) {
		say(
			"林震南磕一磕烟斗，说道：远图公是我的祖父，福威镖局是他一手创办的。当年\n"
			"祖父以七十二路辟邪剑法开创镖局，当真是打遍黑道无敌手。其时白道上英雄见\n"
			"他太过威风，也有去找他比试武艺的，青城派掌门余观主的师父长青子少年之时\n"
			"便在他辟邪剑法下输了几招。\n"
		);
		this_player()->set_temp("marks/林2", 1);
		return 1;
	}
	say("林震南说道：远图公是我的祖父。\n");
	return 1;
}

int ask_pixie()
{
	int p1, p2, p3, p4;

	if (this_player()->query("combat_exp") < 100000) {
		message_vision(
			HIY "$N勃然大怒，喝道：你也窥视我们林家的辟邪剑谱？！我跟你拼了！\n" NOR,
			this_object()
		);
		kill_ob(this_player());
	} else {
		if (this_player()->query("passwd"))
			say("林震南不悦地说道：我不是都告诉你了吗？我的剑法不及先祖。\n");
		else if (this_player()->query_temp("marks/林2")) {
			say(
				"林震南一惊，说道：你怎么知道的？噢，我刚才说露嘴了。嗨，在下的功夫外人\n"
				"不知底细，其实及不上先祖。。\n"
			);
			write("林震南顿一顿，接着对你低声说：先祖去世前，曾给家父留下");
			p1=random(4)+1;
			p2=random(4)+1;
			p3=random(4)+1;
			p4=random(4)+1;
			this_player()->set("passwd", p1*1000+p2*100+p3*10+p4);
			write(chinese_number(this_player()->query("passwd")));
			write("个铜钱，我一直未解其中奥秘。\n");
		} else {
			message_vision(
				HIY "$N勃然大怒，喝道：你也窥视我们林家的辟邪剑谱？！我跟你拼了！\n" NOR,
				this_object()
			);
			kill_ob(this_player());
		}
		this_player()->delete_temp("marks/林1");
		this_player()->delete_temp("marks/林2");
	}
	return 1;
}

int ask_tong()
{
	int p;

	if (!(p=this_player()->query("passwd")))
		say("林震南一脸讥笑的样子，说：怎么混到这一步了到处要钱？\n");
	else {
		write("林震南低声说：先祖去世前，曾给家父留下");
 		write(chinese_number(p));
 		write("个铜钱，我一直未解其中奥秘。\n");
	}
	return 1;
}

int do_accept(string arg)
{
	object ob,cart,biaotou,cloneobj;
	object me,*team,maxplayer,weaponobj;
	int totalexp=0,maxexp,minexp,lev,attr;
	int size,i;
	string* end= ({ "/d/taishan/sjzhuang","/d/xingxiu/xiaowu","/d/shaolin/jxzhuang",
			"/d/hengshan/sanjiaodian","/d/dali/dafujia","/d/xiangyang/shide",
			"/d/huanghe/huanghegate","/d/emei/lingwenge","/d/dali/wuliang/jhg",
			"/d/wudang/sanqingdian","/d/tls/shiyuan","/d/huashan/zhengqi" });
	string* endname= ({ "泰山单家庄","星宿小屋","少林聚贤庄","恒山三教殿","大理大富之家",
			    "温家世德堂","黄河帮寨门","峨嵋灵文阁","无量剑湖宫","武当三清殿",
			    "兜率大士院","华山正气堂" });
	int* timexs= ({ -5,5,0,15,5,-5,0,5,5,5,10,5 });
	mapping skl;
	int * levs,teams,xs;
	string addr,weapon;
	mapping skill_status, map_status;
	string *sname, *mname,* tempstr;
	object* obj;
	string* weapontype=({ "whip","sword","blade","hammer","axe","stick","throwing","staff",
			      "club" });
	string* weaponfile= ({ "bian","changjian","blade1","chui","dafu","zhubang",
			       "feihuangshi","gangzhang","gun" });
	string* emptyhand=({ "cuff","strike","finger","hand","leg","claw" });
	string* clone1=({ "/d/thd/npc/yaoshi","/d/mr/npc/murong-bo","/d/tls/npc/kurong",
			    "/d/dali/wangfu/npc/dzc","/kungfu/class/shaolin/du-nan",
			    "/kungfu/class/gumu/yang","/kungfu/class/gaibang/h7g",
			    "/kungfu/class/emei/mie-jue","/d/huashan/npc/yuebuqun",
			    "/kungfu/class/wudang/zhang"});
	mixed *local = localtime(time() * 60);

	if (arg != "quest") return 0;
	me=this_player();
/*	if ((local[2] < 6 || local[2] >= 21) && !wizardp(me)) {
		command("say 夜间护镖，实在太过危险，我放心不下。");
		return 1;
	}*/
	if (sizeof(filter_array(children(__DIR__"obj/cart"), (: clonep :))) > 7)
	{
		command("say 你来晚了已经有人接下这支镖了。");
		return 1;
	}

	team=me->query_team();
	if (sizeof(team)<2 )
	{
		command("say 护镖路途危险，你这么少的人，我可不放心。");
		return 1;
	}
	else if(sizeof(team)>4)
	{
		command("say 护镖路途危险，单靠人多是没用的。");
		return 1;
	}
	if (team[0]!=me) {
		command("say 只有队伍首领才能提出接镖。");
		return 1;
	}
	for (i=0;i<sizeof(team);i++)
	{
		if (!team[i])
		{
			command("say 你的队伍出现了问题，请解散并重新组建。");
			return 1;
		}
		if (team[i]->query_temp("protecting")) {
			command("say 嗯？你的队伍里怎么有如此贪婪之人？");
			return 1;
		}
		if (!present(team[i]))
		{
			command("say 咦？怎么好象人不全啊？"+team[i]->query("name")+"怎么没来？");
			return 1;
		}
		if (team[i]->query("job_name") == "福州护镖" && !wizardp(team[i])){
			command("say 一直护镖很辛苦的，我看这位"+team[i]->query("name")+RANK_D->query_respect(team[i])+"还是去歇息片刻吧！");
			return 1;
		}
		if (team[i]->query_condition("job_busy") && !wizardp(team[i])){
			command("say 一直护镖很辛苦的，我看这位"+team[i]->query("name")+RANK_D->query_respect(team[i])+"还是去歇息片刻吧！");
			return 1;
		}
                if (me == team[i]) continue;
		if (!interactive(team[i]) || query_ip_number(team[i]) == query_ip_number(me)) {
			command("say 你还是将"+team[i]->query("name")+"换成其他人吧。");
			return 1;
		}
	}
	maxexp=minexp=team[0]->query("combat_exp");
	maxplayer=team[0];
	for (i=0;i<sizeof(team);i++)
	{
		/*if (team[i]->query("combat_exp")<150000)
		{
			command("say 护镖路途危险，我看这位"+RANK_D->query_respect(me)+"需要一个好搭档！");
			return 1;
		}*/
		if (team[i]->query("balance")<1000000)
		{
			command("say 护镖是危险的事，我看"+RANK_D->query_respect(team[i])+"没有赔偿能力。");
			return 1;
		}
		totalexp=totalexp+team[i]->query("combat_exp");
		if(team[i]->query("combat_exp")>maxexp)
		{
			maxexp=team[i]->query("combat_exp");
			maxplayer=team[i];
		}
		else if(team[i]->query("combat_exp")<minexp)
			minexp=team[i]->query("combat_exp");
	}

	if((totalexp<1500000) || ((maxexp-minexp) > 1000000))
	{
		command("say 护镖路途危险，我看诸位似乎无此能力？");
		return 1;
	}

	teams=sizeof(team);
	//选择护镖目的 start
	size=sizeof(end);
	i=random(size);
	addr=end[i];
	xs=timexs[i]*60;
	//选择护镖目的 end
	command("say 请护送这一笔镖银到"+endname[i]+"。\n");
	log_file("job/hubiao",sprintf("%s %s(%s)从林震南这里得到护镖任务，共%s人做，需要送达%s。\n",
		ctime(time())[4..19],me->name(1),
		capitalize(me->query("id")),
		chinese_number(sizeof(team)),endname[i]));

	message_vision("$N将镖队凑齐的押金交给$n。\n", me, this_object());
	say("一队镖车从内院驶出。\n");

	ob=new(__DIR__"obj/cart");
	cart=ob;
	cart->set("long", cart->query("long")+"镖旗上写着"+endname[i]+"几个字。\n");
	cart->set("teamhead",me->query("name"));
	for(i=0;i<sizeof(team);i++) {
		team[i]->set_temp("protecting",cart);
		team[i]->add("balance", -1000000);
		team[i]->apply_condition("job_busy", 45);
		team[i]->set("job_name", "福州护镖");
		team[i]->set_temp("death",team[i]->query("death_count"));
	}
	ob->move(environment());
	cart->set_temp("teams",teams);
	if(teams>3)
		cart->set_temp("team4",team[3]);
	if(teams>2)
		cart->set_temp("team3",team[2]);
	if(teams>1)
		cart->set_temp("team2",team[1]);
	if(teams>0)
		cart->set_temp("team1",team[0]);
	skl = maxplayer->query_skills();
	if(!sizeof(skl))
		lev=100;
	else {
		levs=values(skl);
		lev=0;
		for(i=0;i<sizeof(levs);i++)
		{
			if(levs[i]>lev)
				lev=levs[i];
		}
	}
	attr=lev*10;
	biaotou=new(__DIR__"biaotou");
	biaotou->move(environment());
	biaotou->set_temp("protecting",cart);
	biaotou->set("combat_exp",maxplayer->query("combat_exp"));

	i=random(sizeof(clone1));
	if(!objectp(cloneobj=find_object(clone1[i])))
		cloneobj=load_object(clone1[i]);
	if ( mapp(skill_status = cloneobj->query_skills()) ) {
		sname  = keys(skill_status);

		for(i=0; i<sizeof(skill_status); i++) {
			biaotou->set_skill(sname[i], lev);
		}
	}

	map_status = cloneobj->query_skill_map();
	mname  = keys(map_status);

	for(i=0; i<sizeof(map_status); i++) {
		biaotou->map_skill(mname[i], map_status[mname[i]]);
	}
	obj = all_inventory(maxplayer);
	for(i=0; i<sizeof(obj); i++)
	{
		if((weapon=obj[i]->query("skill_type")) && map_status[weapon]
		    && !obj[i]->query("treasure") && !obj[i]->query("unique")
		    && (obj[i]->query("weapon_prop/damage")>=30) )
		{
			//biaotou->prepare_skill(weapon,map_status[weapon]);
			weapon=file_name(obj[i]);
			tempstr=explode(weapon,"#");
			weapon=tempstr[0];
			weaponobj= new(weapon);
			if (!weaponobj)  return notify_fail("异常错误！\n");
			weaponobj->move(biaotou);
			weaponobj->wield(biaotou);
			break;
		}
	}
	if(i>=sizeof(obj))
	{
		for(i=0;i<sizeof(weapontype);i++)
		{
			if(map_status[weapontype[i]])
			{
				weapon="/clone/weapon/"+weaponfile[i];
				weaponobj= new(weapon);
				if (!weaponobj)  return notify_fail("异常错误！\n");
				weaponobj->move(biaotou);
				weaponobj->wield(biaotou);
				//biaotou->prepare_skill(weapontype[i],map_status[weapontype[i]]);
				break;
			}
		}
	}
	for(i=0;i<sizeof(emptyhand);i++)
	{
		if(map_status[emptyhand[i]])
		{
			biaotou->prepare_skill(emptyhand[i],map_status[emptyhand[i]]);
		}
	}
	biaotou->set("max_qi",attr+100*random(16));
	biaotou->set("eff_qi",biaotou->query("max_qi"));
	biaotou->set("qi",biaotou->query("max_qi"));
	biaotou->set("max_jing",attr+100*random(16));
	biaotou->set("eff_jing",biaotou->query("max_jing"));
	biaotou->set("jing",biaotou->query("max_jing"));
	biaotou->set("max_neili",attr+100*random(16));
	biaotou->set("neili",biaotou->query("max_neili"));
	biaotou->set("eff_jingli",attr+100*random(16));
	biaotou->set("jingli",biaotou->query("eff_jingli"));
	biaotou->set("jiali",lev/5+random(51));
	biaotou->set_temp("apply/damage", lev/3);
	biaotou->set_temp("apply/armor", lev/2);

	ob=new("/clone/money/silver");
	ob->set_amount(100+random(100));
	ob->set("name","镖银");
	ob->move(cart);

	ob=new(__DIR__"biaoshi");
	ob->remove_all_enemy();
	ob->remove_all_killer();
	ob->move(environment());
	//ob->set_leader(biaotou);
	ob->set_temp("protecting",cart);

	ob=new(__DIR__"biaoshi");
	ob->remove_all_enemy();
	ob->remove_all_killer();
	ob->move(environment());
	//ob->set_leader(biaotou);
	ob->set_temp("protecting",cart);

	me->set_temp("target",addr); //设置目标
	me->set_temp("biao_time",time()+xs);
	return 1;
}

int test_dart()
{
	object ob = this_player();

	if (ob->query_condition("job_busy") || ob->query_temp("protecting") || random(100)>50)
	{
		command("say 现在没有镖需要劳驾"+RANK_D->query_respect(ob)+"出马。");
		return 1;
	}

	command("say 现在本镖局有一笔镖银需要运到分局。");
	do_accept("quest");
	return 1;
}
