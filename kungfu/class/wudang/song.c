// song.c 宋远桥

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
string ask_me();
string ask_me1();
string ask_me2();
string ask_me3();
string ask_me4();
int check(object ob);
string get_place(string str);
void create()
{
       set_name("宋远桥", ({ "song yuanqiao", "song" }));
       set("nickname", "武当首侠");
       set("long", 
	       "他就是张三丰的大弟子、武当七侠之首的宋远桥。\n"
	       "身穿一件干干净净的灰色道袍。\n"
	       "他已年过六十，身材瘦长，满脸红光。恬淡冲和，沉默寡言。\n");
       set("gender", "男性");
       set("unique", 1);
       set("age", 61);
       set("attitude", "peaceful");
       set("shen", 10000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);
       set("no_get","宋远桥对你而言太重了。");
       set("no_bark",1);
       
       set("max_qi", 1500);
       set("max_jing", 1000);
       set("neili", 2000);
       set("max_neili", 2000);
       set("jiali", 50);
       set("combat_exp", 1000000);
       set_skill("blade", 130);
       set_skill("cuff", 130);
       set_skill("force", 130);
       set_skill("yinyun-ziqi", 130);
       set_skill("dodge", 130);
       set_skill("wudang-quan", 130);
       set_skill("tiyunzong", 130);
       set_skill("strike", 180);
       set_skill("zhenshan-mianzhang", 180);
       set_skill("parry", 130);
       set_skill("literate", 100);
       set_skill("xuanxu-daofa", 140);
       set_skill("sword", 180);
       set_skill("taiji-jian", 180);
       map_skill("sword", "taiji-jian");
       set_skill("wudang-quan", 140);
       map_skill("force", "yinyun-ziqi");
       map_skill("dodge", "tiyunzong");
       map_skill("strike", "zhenshan-mianzhang");
       map_skill("parry", "zhenshan-mianzhang");
       prepare_skill("strike", "zhenshan-mianzhang");
       create_family("武当派", 2, "弟子");

       set("inquiry", ([
		"秘籍" : (: ask_me :),
		"概要" : (: ask_me1 :),
		"工作" : (: ask_me2 :),
		 "job" : (: ask_me2 :),
		"巡山" : (: ask_me2 :),
	      "fangqi" : (: ask_me3 :),
		"放弃" : (: ask_me3 :),
	     "abandon" : (: ask_me3 :),
		"贡献" : (: ask_me4 :),
		"次数" : (: ask_me4 :),
		"功劳" : (: ask_me4 :),

       ]));
       set("book_count1", 1);
       set("book_count2", 1);
       setup();

       carry_object("/d/wudang/obj/white-robe")->wear();

}

void heart_beat()
{
	::heart_beat();

	clear_conditions_by_type("poison");
	if( !is_fighting() && living(this_object()))
		reincarnate();
}

void init()
{
	object me, ob;
	::init();
	ob = this_player();
	me = this_object();
	if (interactive(ob = this_player()) && !is_fighting()) {
		remove_call_out("greeting");
		call_out("greeting", 0, ob);
	}       
     
}

void greeting(object ob)
{
	int e,p,shen,count,j,i,k;
	mapping fam;

	if (!ob) return;	// Yuj 19991111
	fam = ob->query("family");

	count = ob->query("wd_job",1);
        k = count/50;
        if(k < 50) k = 50;
	j = ob->query("wd/wd_bonus");
	e = 110 * j + random(k);
        if(e > 380) e = 300 + random(e-300);
	p = e/5 + random(e/6) ;
	shen = e*10 + p*10;
	if(ob->query("wd/wd_job_lost2")) {
	    command("faint "+ob->query("id"));
	    command("say "+ob->name()+"，已经有人帮你把那恶贼给赶跑了！");
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_job_lost2");
	    ob->delete("wd/wd_bonus");
	    ob->apply_condition("job_busy", 3);
	}
	if(ob->query("wd/wd_job_lost")) {
	    command("sigh "+ob->query("id"));
	    command("say "+ob->name()+"你怎么搞的，居然让那恶贼给跑了！");
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_job_lost");
	    ob->delete("wd/wd_bonus");
	    ob->apply_condition("job_busy", 3);
	}
	if(ob->query("wd/wd_jobok") ){
	    command("thumb "+ob->query("id"));
	    command("say 很好，祝贺你完成了任务，下去休息休息吧！");
	    ob->add("wd_job",1);
	    count += 1;
	    ob->add("combat_exp",e);
	    ob->add("potential",p);
	    if( ob->query("family") && ob->query("family/family_name")!="桃花岛")
	    ob->add("shen",shen);
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_jobok");
	    ob->delete("wd/wd_bonus");
	    if ( (int)ob->query("potential", 1) > (int)ob->query("max_pot", 1) )
	      ob->set("potential" , ob->query("max_pot", 1) );
	    tell_object(ob, GRN"你获得了"+CHINESE_D->chinese_number(e)+"点经验，"+CHINESE_D->chinese_number(p)+"点潜能！你的侠义正气增加了！\n"NOR);
	    write_file( "/log/job/wd_job",sprintf("%s %s(%s)第%d次任务获得%d点经验，%d点潜能，经验：%d，难度：%d\n",
		 ctime(time()),ob->name(),ob->query("id"),count,e,p,ob->query("combat_exp"),j));
	    i = 40 - ob->query_condition("wd_job");
	    if (i >= 18)
		ob->apply_condition("job_busy", 1);
	    else
		ob->apply_condition("job_busy", (18-i)/3);
	    ob->apply_condition("wd_job", e/100);
	}
	return;
}

void kill_ob(object me)
{
       set("chat_chance_combat", 20);
       set("chat_msg_combat", ({
	       (: perform_action, "strike.bingdi" :),
	       (: perform_action, "dodge.zong" :),
	}));
	::kill_ob(me);       
} 

int accept_fight(object me)
{
	if((int)me->query("shen") < 1) {
	   command("say 习武之人应志在锄恶济善，"+RANK_D->query_respect(me)+"目露瘴气，有违武学之本？");
	   return 0;
	}
	::fight_ob(me);
	 return 1;
}

void attempt_apprentice(object ob)
{
       if ((int)ob->query("shen") < 10000) {
	       command("say 我武当乃是堂堂名门正派，对弟子要求极严。");
	       command("say 在德行方面，" + RANK_D->query_respect(ob) +
		       "是否还做得不够？");
	       return;
       }
       command("say 好吧，贫道就收下你了。");
       command("recruit " + ob->query("id"));
}

string ask_me()
{
       mapping fam; 
       object ob;
       if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派")
	       return RANK_D->query_respect(this_player()) + 
	       "与本派素无来往，不知此话从何谈起？";
       if(query("book_count2") < 1)
	 return "你来晚了，本派的内功心法不在此处。";
       add("book_count2",-1);       
       ob = new(__DIR__"force_book");
       ob->move(this_player());
       return "好吧，这本「太极十三式」你拿回去好好钻研。";
}

string ask_me1()
{
	mapping fam; 
	object ob,song;	
	song = this_object();
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "武当派")
		return RANK_D->query_respect(this_player()) + 
		"与本派素无来往，不知此话从何谈起？";
	if (query("book_count1") < 1)
	   return "你来晚了，刀法概要已经不在此处了。";
	add("book_count1",-1);	 
	ob = new(__DIR__"blade_book");
	ob->move(this_player());
	return "这本书中讲述的刀法要领，你会去好好研究一下。";
}

string ask_me2()
{
	object me, ob, *living, target;
	string str,str2;
	object objwhere;
	int i,j;

	me=this_player();
	str2 = me->query("wd/wd_job_place");

	if (me->query("menggu"))
	      return "哼，你以身属蒙古，还想做什么？";

	if (me->query("wd/wd_job") && !me->query("wd/wd_job_place"))
	      return "啊……，对不起，地点有误，你放弃重新再来吧。";

	if (me->query("wd/wd_job"))
	      return "我不是告诉你了吗，有人在"+ str2 +CYN"附近捣乱。你就快去吧！";

	if (me->query("job_name") =="武当锄奸")
	      return "你刚做完武当锄奸任务，还是先去休息一会吧。";

	if (me->query("shen") < 10000 && !wizardp(me) )
	      return RANK_D->query_respect(me) + "的正气还不够，我无法放心让你做这个任务！";

	if (me->query("combat_exp") < 100000 )
	      return "这位" + RANK_D->query_respect(me) + "武功未成，还是去做别的工作吧！";

	if ( me->query_condition("job_busy")){
	      if (me->query("job_name")=="武当锄奸")
		  return "现在暂时还没有工作让你去做。";
		if( me->query("job_name"))
		  return "你刚做完"+me->query("job_name")+"任务，还是先休息一会吧。";
		return "你正忙着别的事情呢。";
	}

	if (me->query_condition("wd_job"))
	     return "现在暂时没有适合你的工作。";

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (!j || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			objwhere = environment(target);
			str = objwhere->query("short");
			if (!sizeof(objwhere->query("exits"))
			|| str == "武僧堂" 
			|| str == HIR"心禅堂"NOR
			|| str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	} 

	if( !target )
		return "暂时没有任务需要做，你过一会儿再来吧。";

	me->set("wd/wd_job",1);
	me->set("wd/wd_job_place", get_place(base_name(environment(target)))+environment(target)->query("short"));
	me->apply_condition("wd_job",40);
	me->apply_condition("job_busy",40);
	me->set("job_name","武当锄奸");
	command("nod "+me->query("id"));
	ob=new(__DIR__"robber");
	ob->set_temp("target", me->query("id") );
	ob->move(objwhere);
	log_file( "job/wd_job",sprintf("%s %s(%s)开始做wd job,目前实战经验：%d\n", ctime(time()),me->name(),me->query("id"),me->query("combat_exp")));
	command("whisper "+ me->query("id")+" 据说"+ob->query("title")+GRN+ob->query("name")+"正在"+ me->query("wd/wd_job_place") +GRN"附近捣乱，你马上去给我巡视一圈。");
	return "你快去快回，一切小心啊。";
}

string ask_me3()
{
	object ob = this_player();

	if(ob->query("wd/wd_job")){
		ob->delete("wd/wd_job");
		ob->delete("wd/wd_job_place");
		ob->delete("wd/wd_bonus");
		return ob->name()+"，你太让我失望了，居然这么点活都干不好，先退下吧！";
	}
	return ob->name()+"，你又没在我这里领任务，瞎放弃什么呀！";
}

string ask_me4()
{
	object ob;
	ob = this_player();
	if(!ob->query("wd_job")){
	    return "对不起，"+ob->name()+"，你好象还没有在我这里领过任务呢，加油干吧！";
	}
	return ""+ob->name()+"，你已经成功地铲除了"+CHINESE_D->chinese_number((int)ob->query("wd_job"))+"名恶贼！";
}

void destroying(object obj)
{     
	if (!obj) return;
	if (userp(obj)) command("drop "+obj->parse_command_id_list()[0]);
	  else destruct(obj);
}

void die()
{
	object ob;
	if (!query_temp("living"))
	{
		ob = new("/kungfu/class/wudang/song");
		ob->move("/d/wudang/sanqingdian");
	}
	::die();
}

string get_place(string str)
{ 
	string *place = explode(str, "/");

	str = "";
	if(place[0] == "d")
		switch(place[1]){
			case "baituo":    str = "西域白陀山";  break;
			case "hj":	str = "西域回疆"; break;
			case "mingjiao":  str = "西域明教"; break;
			case "shaolin":   str = "河南嵩山少林"; break;
			case "songshan":  str = "河南嵩山"; break;
			case "wudang":    str = "湖北武当山"; break;
			case "xingxiu":   str = "西域星宿海"; break;
			case "city":      str = "江南扬州城"; break;
			case "emei":      str = "四川峨嵋山"; break;
			case "fuzhou":    str = "南疆福州"; break;
			case "jiaxing":   str = "江南嘉兴"; break;
			case "taishan":   str = "山东泰山"; break;
			case "dali":      
			switch(place[2]) {
				case "daliwest":	str = "西南大理国西";	break;
				case "dalisouth":	str = "西南大理国南";	break;
				case "dalieast":	str = "西南大理国东";	break;
				case "wuliang":		str = "无量山";		break;
				case "dlhg":		str = "西南大理国皇宫";	break;
				case "wangfu":		str = "西南大理国王府";	break;
				case "yideng":		str = "桃源县";		break;
				case "yuxu":		str = "玉虚观";		break;
				default : 		str = "西南大理国";		break;
			}
			break;
			case "tls":       str = "大理天龙寺"; break;
			case "tiezhang":  str = "湖南铁掌山"; break;
			case "kunlun":    str = "";break;
			case "fairyland": str = "西域昆仑山"; break;
			case "gumu":      str = ""; break;
			case "chengdu":   str = "四川成都"; break;
			case "huashan":   str = "陕西华山"; break;
			case "xiangyang": str = "湖北襄阳"; break;
			case "xueshan":   str = "西番大雪山"; break;
			case "wizard":    str = ""; break;
			case "death":     str = ""; break;
			case "gaibang":   str = "丐帮分舵"; break;
			case "hz":	str = "江南杭州"; break;
			case "village":   str = "陕西小村"; break;
			case "wuguan":    str = "襄阳武馆"; break;
			case "thd":       str = "东海桃花岛"; break;
			case "gaibang":   str = "丐帮分舵"; break;
			case "mr":	str = "苏州燕子坞"; break;
			case "suzhou":    str = "苏州县城"; break;
			case "sld":       str = "北海神龙岛"; break;
	}
	return str;
}

string *no_kill_list = ({
	 "mu ren", "jin ren", "yin ren", "zhong shentong", "zhu cong", "shi ren", "huo du","he shiwo"
});

int check(object ob)
{
	object room;
	string room_name;
	
	if(!objectp(ob)
	 || !ob->query("startroom")      // add by Yuj@SJ to void job NPC
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || member_array(ob->query("id"), no_kill_list) != -1
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || !objectp(room=environment(ob))
	 || room->query("no_fight") 
	 || room->query("outdoors") == "昆仑翠谷"
	 || strsrch(room_name = file_name(room),"/d/") != 0
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/kunlun/") == 0
	 || strsrch(room_name, "/d/mingjiao/lsd/") == 0
	 || strsrch(room_name, "/d/mingjiao/bhd/") == 0
	 || strsrch(room_name, "/d/wudang/") == 0
	 || strsrch(room_name, "/d/shaolin/liwu") == 0
	 || strsrch(room_name, "/d/shaolin/houyuan") == 0
	 || strsrch(room_name, "/d/huashan/jiabi") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/shaolin/xinchan") == 0
	 || strsrch(room_name, "/d/mingjiao/yuanzi") == 0
	 || strsrch(room_name, "/d/mingjiao/wxiang") == 0
	 || strsrch(room_name, "/d/baituo/") == 0
	 || strsrch(room_name, "/d/thd/") == 0
	 || strsrch(room_name, "/d/sld/") == 0) 
	 return 0;
	return 1;
}
