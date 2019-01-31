// wizardb.c

#include <ansi.h>
#include <localtime.h>

inherit NPC;

int ask_name();
int ask_guild();
int ask_me_1();
int ask_fy();
int ask_cgift();
int ask_sjsz();
int ask_duihuan();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
	set_name("巫师",({  "wizard", "wushi" }) );
        set("gender", "男性" );
        set("age", 30);
        set("long", "这是一个成天无所事事的巫师。你可以询问他“初出茅庐”、“试剑山庄”、“属性调整”、“积分兑换”和“福源”的问题。\n");

        set("str", 17);
        set("dex", 16);
        set("con", 15);
        set("int", 17);
        set("shen_type", 1);
        set_temp("apply/defense", 10);
        set("combat_exp", 100);
        set("attitude", "peaceful");
        set("inquiry", ([
	"name": (: ask_name :),
	"初出茅庐": (: ask_me_1 :),
//              "开站奖励": (: ask_me_2 :),
                 "试剑山庄": (: ask_sjsz :),
                "属性调整": (: ask_cgift :),
                "积分兑换": (: ask_duihuan :),
                "福源": (: ask_fy :),
		"rumors": "听说玩家自建帮派系统进入开放阶段了。",
        	"bbb": "见到帮主我，难道没有任何表示吗？",
		"建帮": (:ask_guild :),
         	"杀手": "见到帮主我，难道没有任何表示吗？",
	]) );

        carry_object("/clone/misc/cloth")->wear();
        setup();
}

int ask_name()
{
	object ob = this_player();

	command("smash " + ob->query("id"));
	say("没搞错吧？一声不吭就smash别人？准是BBB。\n");
	return 1;
}

int ask_fy()
{
	object me = this_player();
        int i;
        i = me->query("kar");
        command("say 你目前的福源是" + chinese_number(i) + "。\n");
        return 1;
}

int ask_guild()
{
	object ob = this_player();
	int exp = ob->query("combat_exp");
	if (exp >= 2000000 && (!present("lingpai",ob)))
	{
          	new("/data/group/obj/ling")->move(ob);
		say("巫师说道：把令牌拿去吧。帮派系统，有建议、BUG 请向 bbb 报告。\n");
	}
	if ( exp < 2000000 )
		say("巫师说道：你的经验不够，暂时不能创建帮派。\n");
	if ( present("lingpai",ob))
		say("巫师说道：你已经有令牌了。\n");
	else	say("巫师说道：条件不符合，不能创建帮派。\n");
	return 1;
}

int ask_me_1()
{
	object me = this_player();
	
	if( me->query("combat_exp") < 100000 ) {
		command("disapp "+(string)me->query("id"));
		command("say 你的经验不足，还是继续努力吧！\n");
		return 1;
	}

	if( me->query("gift_2013") ) {
		command("hmm "+(string)me->query("id"));
		command("say 你已经领过礼物了。\n");
		return 1;
	}

	me->set("gift_2013", 1 );
	me->add("neili", 100 );
	me->add("max_neili", 100 );
	me->add("jingli", 100 );
	me->add("max_jingli", 100 );
        if( me->query_skill("force",1) > 80 ) {
         	me->add("balance", 2000000 );
	}
        me->setup();
	  me->add("potential", 2000 );
        me->add_busy(1 + random(2));
        write(HIY"你获得一份"HIW"新年礼物"HIY"，高兴地手舞足蹈起来!\n"NOR);
        return 1;
}

int ask_sjsz()
{
        object ob,me,*thing;
        int i, time;
		int sysdate;
		
		me = this_player();

		//for old data
	if (me->query("sjsz_enter_time"))
	     set_enter_date(me,me->query("sjsz_enter_time"));

	if (me->query("sjsz_enter_time")=="2013119")
	     me->delete("sjsz_enter_time");

	ob = load_object("/clone/npc/zhong-shentong");


	if( me->query("id") == ob->query("winner") ) {
             command("say 中神通可不能去试剑山庄。\n");
             return 1;
        }

        if( me->query_condition("killer") && !wiz_level(me) ) {
             command("say 通缉犯可不能去试剑山庄。\n");
             return 1;
        }
        if( me->query("balance") < 2000000 ) {
             command("say 你的银行存款不够，不能进入试剑山庄。\n");
             return 1;
        }
        if( me->query("combat_exp") < 2000000 ) {
	       command("disapp "+(string)me->query("id"));
		 command("say 你的经验不足，还是继续努力吧！\n");
		 return 1;
	  }
	sysdate=query_date(time());
	if( me->query("sjsz_enter_date") && sysdate <= me->query("sjsz_enter_date") ) {
             command("say 一天只能进入试剑山庄一次，你明天再来吧。\n");
			  tell_object(me,HIG"你上次进入试剑山庄是在"+CHINESE_D->chinese_date(me->query("sjsz_enter_time"),1)+"。\n"NOR);
             return 1;
        }
	
		thing = deep_inventory(me);
		i = sizeof(thing);
	  while (i--)
	       if (thing[i]->is_character()) {
		   message_vision("巫师突然把眼一瞪，道：你还想带个人进去？\n", me);
	         command("knock "+(string)me->query("id"));
		   command("say 你慢慢发呆吧！\n");
		   me->add_busy(100 + random(200));
	         return 1;
		} 

        me->add("balance", -2000000);
        command("nod "+(string)me->query("id"));
        command("say 好吧，我现在就送你去试剑山庄。\n");
        me->set("sjsz_enter_time",time());
		set_enter_date(me,time());
		


        me->apply_condition("sjsz_time",60);
        me->move("/cmds/leitai/bwdh/gate");
        CHANNEL_D->do_channel( this_object(), "rumor",
        sprintf("%s开始试剑山庄的冒险了！", me->name(1)));
        return 1;
}
private void set_enter_date(object ob,int date)
{
		mixed *local;
		int y, m, d;
		string sjsz_enter_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON];
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          sjsz_enter_date=y+"0"+m+"0"+d;
		      else
			        sjsz_enter_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          sjsz_enter_date=""+y+m+"0"+d;
		      else
			        sjsz_enter_date=""+y+m+d;
                  }

		ob->set("sjsz_enter_date",sjsz_enter_date);

}
private int query_date(int date)
{
		mixed *local;
		int y, m, d;
		string query_date;
		
		local = localtime(date);
		d = local[LT_MDAY];
		m = local[LT_MON];
		y = local[LT_YEAR];
		
		if (m<10) {
                  if (d<10)  
                          query_date=y+"0"+m+"0"+d;
		      else
		              query_date=y+"0"+m+d;
                  }
            else {
                  if (d<10)  
                          query_date=""+y+m+"0"+d;
		      else
			        query_date=""+y+m+d;
                  }

		return (int)query_date;

}

int ask_cgift()
{
	object me = this_player();
	if( me->query("combat_exp") < 100000 ) {
		command("disapp "+(string)me->query("id"));
		command("say 你的经验不足，继续努力吧！\n");
		return 1;
	}

	if( me->query("cgift_2013") ) {
		command("hmm "+(string)me->query("id"));
		command("say 你已经问过了，怎么还问啊。\n");
                me->add_busy(50);
		return 1;
	}

	me->set("cgift_2013", 1 );
        me->set_temp("cgift", 1 );
        me->add_busy(1 + random(2));
        write(HIY"你已获得一次cgift指令使用机会，请在下线前使用!修改先天属性将会扣除经验，请慎重使用！\n"NOR);
        return 1;
}

int ask_duihuan()
{
	object me = this_player();
	int i,time;

        time = time()- me->query("duihuan_time");

        if( me->query("duihuan_time") && time < 604800 ) {
             tell_object(me,HIG"看起来巫师在"+CHINESE_D->chinese_time(604800-time)+"之内不打算答复你关于积分兑换的问题。\n"NOR);
             return 1;
        }

        switch( random(8) ){
		case 0:	i = me->query("dali_job");
                        if (i > 500 ) {
                        	i = i - 500;
                        	me->add("dali_job",-500);
                        	me->add("sj_credit",20);
                        	command("say 你使用500次大理送信任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用500次大理送信任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的大理送信任务次数不足500次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 1:	i = me->query("hs_job");
                        if (i > 500 ) {
                        	i = i - 500;
                        	me->add("hs_job",-500);
                        	me->add("sj_credit",20);
                        	command("say 你使用500次华山任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用500次华山任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的华山任务次数不足500次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 2:	i = me->query("job_time/长乐帮");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("job_time/长乐帮",-400);
                        	me->add("sj_credit",20);
                        	command("say 你使用400次长乐帮任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用400次长乐帮任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的长乐帮任务次数不足400次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 3:	i = me->query("wd_job");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("wd_job",-400);
                        	me->add("sj_credit",20);
                        	command("say 你使用400次武当任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用400次武当任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的武当任务次数不足400次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 4:	i = me->query("xs_job");
                        if (i > 400 ) {
                        	i = i - 400;
                        	me->add("xs_job",-400);
                        	me->add("sj_credit",20);
                        	command("say 你使用400次雪山任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用400次雪山任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的雪山任务次数不足400次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 5:	i = me->query("gb_job");
                        if (i > 300 ) {
                        	i = i - 300;
                        	me->add("gb_job",-300);
                        	me->add("sj_credit",20);
                        	command("say 你使用300次丐帮吴长老任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用300次丐帮吴长老任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的丐帮吴长老任务次数不足300次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 6:	i = me->query("songshan_point");
                        if (i > 300 ) {
                        	i = i - 300;
                        	me->add("songshan_point",-300);
                        	me->add("sj_credit",20);
                        	command("say 你使用300次嵩山任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用300次嵩山任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的嵩山任务次数不足300次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		case 7:	i = me->query("gb_job4");
                        if (i > 100 ) {
                        	i = i - 100;
                        	me->add("songshan_point",-100);
                        	me->add("sj_credit",20);
                        	command("say 你使用100次丐帮颂摩崖任务次数兑换了20点副本点数。\n");
                        	CHANNEL_D->do_channel( this_object(), "chat",
                        	sprintf("%s使用100次丐帮颂摩崖任务次数兑换了20点副本点数。", me->name(1)));
                        } else {
                        	command("say 你的丐帮颂摩崖任务次数不足100次，请下次再来。\n");
                        	me->set("duihuan_time",time());
                        	}
			break;
		default: break;
	}

	return 1;

}