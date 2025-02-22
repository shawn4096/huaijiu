// /d/mr/npc/murong-fu.c  慕容复
// by leontt /12/05/2000
// by tiantian@sj 6/3/2000 fix mr job bug
// Modify By River@SJ 修正 job，另外门派drug全部cut 12/08/Y2k

inherit NPC;
#include <ansi.h>
#include <combat.h>
#include "skill.h"
int ask_fuming(string arg);
mixed ask_bo();
string ask_fenglu();
mixed ask_sword2();
string ask_skill();
string ask_wang();
string ask_learn();
string ask_dan();
string ask_dan1();
string ask_ge();
string ask_sword();
string ask_book();
string ask_book2();
string ask_times();
string ask_9dan();
int ask_fangqi();

void create()
{
	object weapon;
	set_name("慕容复",({"murong fu","murong","fu"}));
	set("title","姑苏慕容公子");
	set("nick","以彼之道 还施彼身");
	set("long",
		"他就是天下号称以彼之道，还施彼身的姑苏慕容复。\n"
		"他脸上带着不可一世的笑容。\n");
	set("age", 27);
	set("attitude", "friendly");
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	set("no_get", "慕容复背不起来。\n");

	set("max_qi",3500);
	set("max_jing", 3000);
	set("eff_jingli", 4000);
	set("neili",3500);
	set("max_neili", 3500);
	set("jiali", 1);
	set("combat_exp", 1500000);
	set("dan", 10);
	set("shen", -1000);
	set("no_bark",1);
	set("chat_chance_combat", 25);
	set("chat_msg_combat", ({
		(: exert_function, "shenyuan" :),
		(: perform_action, "strike.riyue" :),
		(: perform_action, "finger.ci" :),
		(: perform_action, "sword.lianhuan" :),
	}));
	set_skill("strike",170);
	set_skill("finger",170);
	set_skill("dodge",180);
	set_skill("force", 170);
	set_skill("canhe-zhi", 160);
	set_skill("murong-jianfa",170);
	set_skill("shenyuan-gong", 180);
	set_skill("yanling-shenfa", 160);
	set_skill("xingyi-zhang",170);
	set_skill("douzhuan-xingyi", 180);
	set_skill("parry", 180);
	set_skill("sword", 270);
	set_skill("literate", 170);
	set_skill("murong-daofa", 160);
	set_skill("blade",160);
	set_skill("xingyi-jianzhen",170);

	map_skill("blade", "murong-daofa");
	map_skill("finger", "canhe-zhi");
	map_skill("force", "shenyuan-gong");
	map_skill("dodge", "yanling-shenfa");
	map_skill("strike", "xingyi-zhang");
	map_skill("parry", "murong-jianfa");
	map_skill("sword", "murong-jianfa");

	prepare_skill("finger","canhe-zhi");
	prepare_skill("strike","xingyi-zhang");

	create_family("姑苏慕容", 2, "弟子");

	set("inquiry",
		([
			"name" : "我就是以彼之道，还施彼身的姑苏慕容复。\n",
			"here" : "这里是大名鼎鼎的燕子坞，难道你没有听说过？\n",
			"rumors" : "家父突染恶疾，我连他老人家最后一面都没见到，此事顶有蹊跷！\n",
			"姑妈" : "我的姑妈住在曼佗罗山庄，那里有闻名天下的娘缳玉洞。\n",
			"还施水阁" : (: ask_ge :),
			"慕容博" : (: ask_bo :),
			"领悟" : (: ask_book :),
			"俸禄" : (: ask_fenglu :),
			"王语嫣" : (: ask_wang :),
			"碧玉剑" : (: ask_sword2 :),
			"宝剑" : (: ask_sword :),
			"次数" : (: ask_times :),
			"斗转星移"  : (: ask_skill :),
			"图解" : (: ask_book2 :),
			"武学" : (: ask_learn :),
			"复命" : (: ask_fuming :),
			"放弃" : (: ask_fangqi :),
		])
	);
	set("dan_count", 2);
	set("book_count",1);
	set("book2_count" ,1);
	set("dan1_count", 2);
	setup();
	if (clonep()) {
		weapon = unew(BINGQI_D("sword/biyu-jian"));
		if (!weapon) weapon = unew(BINGQI_D("changjian"));
		weapon->move(this_object());
		weapon->wield();
		add_money("gold", 5);
	}
}
void init()
{
	::init();
	add_action("do_jiaoliang", "jiaoliang");
}

void attempt_apprentice(object ob)
{
	if (ob->query_skill("parry", 1) < 120) {
		command("say 我姑苏慕容以彼之道、还施彼身对招架要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
		return;
	}

	if (ob->query_skill("shenyuan-gong", 1) < 100) {
		command("say 我姑苏慕容以彼之道、还施彼身对内功心法要求甚高。");
		command("say " + RANK_D->query_respect(ob) + "的功力不够，还是请回吧。");
		return;
	}

	command("say 嗯，看你还是个学武的料，我就收下你吧！");
	command("say 苍天在上，让我姑苏慕容又得一良材，为复兴我大燕多了一份力量。");
	command("chat* 朗声说道：公子我又收一良材，大燕兴复指日可待啦！");
	command("chat* haha");
	command("recruit " + ob->query("id"));
}

string ask_fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if ( !fam || fam["family_name"] != "姑苏慕容")
		return "这位"+ RANK_D->query_respect(ob) +"不是我慕容弟子，此话从何说起？";
	switch ( fam["generation"] ) {
		case 2:
			gold += 1000;
		case 3:
			gold += 1500;
			break;
		default:
			return "这位"+ RANK_D->query_respect(ob) +"在我姑苏慕容的身份太低，现在还没有资格领取俸禄。";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "这位"+RANK_D->query_respect(ob) +"本月已经领过俸禄了，还是等下个月再来吧。";
	gold *= ob->query_skill("shenyuan-gong",1);
	if (gold < 1) return "你这个月没有俸禄。";
	ob->set("fenglu", fenglu);
	command ("addoil " + ob->query("id"));
	ob->add("balance", gold);
	return "你本月的俸禄"+MONEY_D->money_str(gold)+"已经存入钱庄了，但愿这位"+ RANK_D->query_respect(ob) +"不要使我失望，好好干吧！";
}

mixed ask_sword2()
{
	object me=this_player(), weapon;
	mapping fam;

	if (!(fam = me->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(me)+"与本派素无来往，不知此话从何谈起？";
	weapon = present("biyu jian", this_object());
	if(!objectp(weapon))
		weapon = unew(BINGQI_D("sword/biyu-jian"));
	if(!objectp(weapon))
		return "碧玉剑已经被人拿走了, 现在不在我手里。";
	command("unwield biyu jian");
	weapon->move(me);
	command("wield jian");
	message_vision("$N给了$n一把碧玉剑。\n", this_object(), me);
	return 1;
}

string ask_wang()
{
	mapping fam;

	if (!fam = this_player()->query("family") || fam["family_name"] !="姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "语嫣是我表妹，一直被姑妈管的很严，连我都很长时间没有见到她了。";
}

string ask_skill()
{
	mapping fam;

	if (!(fam = this_player()->query("family"))|| fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "斗转星移是我慕容家的绝学，最是注重招架和身法。";
}

string ask_ge()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "还施水阁是我慕容收藏天下秘籍之所在，在我的书……";
}

string ask_sword()
{
	mapping fam;

	if (!(fam = this_player()->query("family")) || fam["family_name"] != "姑苏慕容")
		return RANK_D->query_respect(this_player()) + "与本派素无来往，不知此话从何谈起？";
	return "碧玉剑是老爷子仙逝后的遗物，我让阿朱姑娘收起来好好保管！";
}

string ask_book()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) +
		"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(me) + "功力不够，何以谈及领悟？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(me) +
		"现在身上不是有斗转星移的武籍了吗？怎么又来要了？ 真是贪得无厌！";

	ob = unew("/d/mr/obj/shu1");
	if(!clonep(ob))
		return "斗转星移武籍已经被别人要走了。";

	ob->move(me);

	message_vision("$N得到一本斗转星移的武功秘籍。\n", me);
	return "好吧，看你为慕容家忠心耿耿，这本书就赐于你吧。";
}

string ask_book2()
{
	object me = this_player();
	object ob;

	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) +
		"与本派素无来往，不知此话从何谈起？";

	if (me->query_skill("parry",1) < 121)
		return RANK_D->query_respect(this_player()) + "功力不够，何以谈及领悟？";

	if (me->query_skill("douzhuan-xingyi",1)<50)
		return RANK_D->query_respect(me) +
		"功力不够，何以谈及领取图解？";
	if (present("douzhuan xingyi", me))
		return RANK_D->query_respect(this_player()) +
		"你现在身上不是有斗转星移的武籍了嘛，怎么又来要了？ 真是贪得无厌！";

	ob = unew("/d/mr/obj/shu2");
	if (!clonep(ob))
		return "对不起，斗转星移的武籍已经被别人要走了。";

	ob->move(this_player());
	message_vision("$N得到一本斗转星移的武功秘籍。\n", me);
	return "好吧，看你为慕容家忠心耿耿，这本书就赐于你吧。";
}

mixed ask_bo()
{
	object me = this_player();
	object ob = this_object();

	if (me->query_temp("marks/失败")) {
		message_vision(
			"$N眼中发出两道寒光直射$n，一字一字地说道：已经较量过了，你怎么还不回去安心练功呢！\n",
			ob, me
		);
		return 1;
	}
	if (me->query("family/family_name") != "姑苏慕容")
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

	if (me->query("family/generation") != 3)
		return RANK_D->query_respect(me) + "为何开这等玩笑？";

	if (me->query_temp("marks/bai_bo"))
		return "你已经可以去见家父，不用再向我学了！";

	message_vision(
		"$N眼中发出两道寒光直射$n，一字一字地说道：家父现在身处少林，那里藏龙卧虎，\n"
		"你若武功未成，最好不要去自取其辱；如果你有信心，就和我较量一下。(jiaoliang)\n",
		ob, me
	);

	me->set_temp("marks/jiao", 1);
	return 1;
}

int do_jiaoliang()
{
	object me, obj, jiaxin;
	int current_qi;
	int i;

	me = this_object();
	obj = this_player();

	if (obj->query_temp("marks/jiao")) {
		message_vision("$N对$n说：好吧，那就请师父指点几招。\n", obj, me);
		set("max_qi", 3500);
		set("jiali", 10);
		set("neili", 3500);
		set("max_neili", 3500);
		current_qi = set("qi", 3500);

		i=10;
		obj->delete_temp("marks/jiao");
		while ((obj->query("qi")*100 / (int)obj->query("max_qi")) > 30) {
			if (!present(obj, environment()))
				return 1;
			i--;
			COMBAT_D->do_attack(obj, me, obj->query_temp("weapon"), 1);
			if (!i || (me->query("qi")*100/current_qi) < 30) {
				message_vision(
					"$N对$n说道：不想我慕容世家又出良材，我这就写封家信，你马上动身前去少林，\n"
					"把它交给家父。希望你能不负众望，振兴慕容世家，光复大燕国。\n",
					me, obj
				);
				jiaxin = new("/d/mr/obj/jiaxin");
				jiaxin->move(obj);
				obj->set_temp("marks/bai_bo", 1);
				message_vision("$N交给$n一封家信\n", me, obj);
				return 1;
			}
			COMBAT_D->do_attack(me, obj, me->query_temp("weapon"), 1);
		}
		message_vision(
			"$N对着$n冷冷说道：你武功未成，就好高骛远，你还是安心练功去吧！\n",
			me, obj
		);
		obj->set_temp("marks/失败", 1);
	}
	return 1;
}

string ask_learn()
{
	int j=random(sizeof(my_skills));
	mapping skill = my_skills[j];
	int i;
	object me = this_player();
	string skill_name;

	i = 7+random(5);
	if (me->query("family/family_name") != "姑苏慕容") // 必须是慕容派弟子
		return RANK_D->query_respect(me) + "与本派素无来往，不知此话从何谈起？";

	if (me->query("combat_exp") > 2000000 )
		return RANK_D->query_respect(me)
		+ "你已经尽数掌握了精深奥妙的武学诀要，我可不敢劳您的大架了。";

	if (me->query_skill("parry", 1) < 100 ) // 招架必须大于等于100级
		return RANK_D->query_respect(me) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if (me->query_skill("douzhuan-xingyi", 1) < 100 )  // 斗转星移必须大于等于100级
		return RANK_D->query_respect(me) +
		"于本门武学尚不能运用自如，如何谈及天下之武学？";
	if (me->query_condition("mr_job") )
		return RANK_D->query_respect(me) +
		"还没完成我交给你的任务呢。";
	if (is_fighting())
		return "嚷什么嚷，没看见我这正忙着呢吗？";
	if (me->query("job_name") =="慕容偷学")
		return RANK_D->query_respect(me) +
		"先等等吧，我现在没有什么感兴趣的武功想学。";
	if (me->query_condition("wait_mr_job", 1) > 0)
		return RANK_D->query_respect(me) +
		"先等等吧，我现在没有什么感兴趣的武功想学。";

	if(!skill["skill_id"])
		return sprintf("SKILL.H文件在第%d个技能出错，请通知巫师修改。\n",j);
	skill_name = to_chinese(skill["skill_id"]);
	me->set_temp("skill_target", skill_name);  // 此标记表明此次偷学目标技能的中文名字
	me->set_temp("skill_id", skill["skill_id"]); // 此标记表明此次偷学目标技能的英文名字
	me->set_temp("skill_type", skill["skill_type"]); // 此标记表明此次偷学目标技能的英文类型
	me->set_temp("skill_lvl", i); // 此标记表明此次偷学目标技能所需要的级别
	me->apply_condition("mr_job", 30+random(15)); // 设置此次任务必须在所需时间内完成;
	me->apply_condition("job_busy",9);
	me->set("job_name", "慕容偷学");
	command( "whisper "+me->query("id") + " 我姑苏慕容傲视天下所有武功，但也不乏为之羡慕的。");
	command("whisper "+ me->query("id")
	+ " 好吧，"+"「"+skill_name+"」"+"「"+skill["skill_id"]+"」我垂涎已久，你们把它学回来，我大大的有赏。");

	new("/d/mr/obj/paper")->move(me);

	if (random(2))
		return "今天天气就是好，就是好。";
	return "今天天气真不错。";
}

int ask_fuming(string arg)
{
	object me, ob;
	int bouns,My_exp,Target_exp,pot;
	float rate;

	me = this_player();
	ob = this_object();

	if( !arg)
	{
		command("say 你要展示什么？");
		return 1;
	}

	if( !me->query_condition("mr_job"))
	{
		command("say 你现在没有任务吧？");
		return 1;
	}

	if( me->is_busy())
	{
		command("say 你正忙着呢，有什么事情呆会再说。");
		return 1;
	}

	if( me->is_fighting())
	{
		command("say 你正打架呢，有什么事情呆会再说。");
		return 1;
	}

	if(!me->query_temp("job_done"))
	{
		command("say 你学到什么东西了？还有脸敢回来？");
		return 1;
	}

	if( this_object()->is_fighting())
	{
		command("say 嚷什么嚷，没看见我这正忙着呢吗？");
		return 1;
	}

	Target_exp = me->query_temp("master_exp");
	My_exp= me->query("combat_exp");

	me->add("mr_job",1);
	bouns = me->query_temp("skill_lvl")*5/2;
	bouns +=  me->query_skill("douzhuan-xingyi",1) * 5 / 3;

	rate = to_float(Target_exp)/to_float(My_exp);
	if (rate > 2) rate = 2;
	if (rate < 0.6) rate = 0.6;
	bouns *= rate;

	message_vision(CYN"慕容复仔细研究着$N记在纸卷上的武功精要，情不自禁地说道：好一个"+me->query_temp("skill_target")+"。\n"NOR, me);
	message_vision(CYN"慕容复拍了拍$N的头，对$P说道：辛苦你了，下去休息吧。\n"NOR, me);
	if (bouns > 800) bouns = 600 + random((bouns-250)/5);
	me->add("combat_exp", bouns);
	me->improve_skill("douzhuan-xingyi", me->query_int()*2);
	pot = bouns/6+random(bouns/10);
	if (me->add("potential", pot) > me->query("max_pot"))
		me->set("potential", me->query("max_pot"));
	write(GRN"你获得了"+(string)(bouns)+"点经验和"+pot+"点潜能的奖励\n"NOR);
	write(GRN"你已经为慕容世家做了"+me->query("mr_job")+"次任务!\n"NOR);

	log_file("job/mrjob",
	sprintf("%s(%s) touxue %s(%s) on %s, exp=%d,job times=%d.\n",
		me->name(1), geteuid(me),
		me->query_temp("skill_target"), me->query_temp("skill_id"), ctime(time()), bouns,me->query("mr_job")));

	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(10)+5);

	if(present("paper", me))
	{
		destruct(present("paper",me));
	}

	return 1;

}

int ask_fangqi()
{
	object me=this_player(),obj;

	if( !me->query_condition("mr_job") )
	{
		command("say 你现在没有任务吧？");
		return 1;
	}

	command( "say 也好，那么你先下去休息一会吧。" );
	command( "disapp");
	command( "sigh "+me->query("id"));
	obj=me->query_temp("dizi");
	if( objectp(obj) )
		destruct(obj);
	me->delete_temp("skill_target");
	me->delete_temp("skill_id");
	me->delete_temp("skill_type");
	me->delete_temp("skill_lvl");
	me->delete_temp("job_done");

	me->clear_condition("mr_job");
	me->apply_condition("wait_mr_job", random(2)+2);
		me->add("combat_exp",-10-random(10));
		return 1;
}

string ask_times()
{
	object ob;
	ob = this_player();
	if(!ob->query("mr_job"))
	{
	 return "很遗憾，"+ob->name()+"，你好象没有为慕容做过贡献！";
	}
	return ""+ob->name()+"，你已经完成了"+CHINESE_D->chinese_number((int)ob->query("mr_job"))+"次慕容偷学任务！";
}
