//by cool 98.3.25
// 不能和wd,xs job一起做。River@SJ 2000.7.19

inherit NPC;
#include <ansi.h>
string get_place(string str);
int check(object ob);
string ask_job();
string ask_fangqi();

void create()
{
	set_name("褚万里", ({ "zhu wanli","zhu","wanli" }));
	set("title", "大理国镇南王府家将");
	set("gender", "男性");
	set("age", 33);
	set("str", 27);
	set("dex", 26);
	set("long", "这人身穿军服，腰上插着一根软索，英气逼人。\n");
	set("combat_exp", 400000);
	set("shen_type", 1);
	set("attitude", "peaceful");
	set("no_bark",1);
	set_skill("unarmed", 100);
	set_skill("force", 100);
	set_skill("whip", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_temp("apply/attack", 70);
	set_temp("apply/defense", 70);
	set_temp("apply/armor", 70);
	set_temp("apply/damage", 20);

	set("max_qi", 900);
	set("neili", 900); 
	set("max_neili", 900);
	set("jiali", 20);
	set("inquiry", ([
	     "送信" : (: ask_job :),
		 "job" : (: ask_job :),
		 "fangqi" : (: ask_fangqi :),
		 "放弃" : (: ask_fangqi :),
	]));

	setup();
	carry_object(BINGQI_D("ruansuo"))->wield();
	carry_object(ARMOR_D("junfu"))->wear();
}

string ask_job()
{
	object me, *living, target, ob, obj;
	int time,i,j;
	string str;

	ob=this_player();
	me=this_object();

	if (!wizardp(ob) && !ob->query_temp("dali_join"))
		return RANK_D->query_respect(ob) +"，你不是本王府随从，此话从何说起？";

	if (ob->query_temp("dali_songxin"))
		return "你不是已经领了送信的任务吗？还不快去做。";

	if (ob->query("job_name") == "大理送信")
		return "你刚做完大理送信任务，还是去休息一会吧。";

	if (ob->query_condition("dali_songxin") > 0)
		return "现在暂时没有给你的任务，再等"+chinese_number((ob->query_condition("dali_songxin")+5)/6)+"个时辰吧。";

	if( ob->query_condition("job_busy"))
		return "你现在正忙着做其他任务呢！";

	if (ob->query("combat_exp") < 100000)
		     return ("你的功夫还不够啊，送信可是很危险的事，我可不敢交给你这任务。");

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "武僧堂" 
			 || str == HIR"心禅堂"NOR
			 || str == "金刚伏魔圈" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	} 

	if( !target )
		return "暂时没有信需要送，你过一会儿再来吧。";
	
	time = random(10)+ 25;
	ob->delete_temp("songxin_ok");
	ob->delete_temp("dali_songxin_late");
	ob->set_temp("dali_songxin",1);
	ob->set_temp("songxin_time",time);
	ob->delete_temp("songxin_zuji");
	ob->apply_condition("job_busy", time);
	ob->set("job_name", "大理送信");

	if (random(2)) {
		ob->apply_condition("dali_songxin",time);
		ob->set_temp("songxin_target_name", target->query("name"));
		ob->set_temp("songxin_id",target->query("id"));
	} else {
		ob->apply_condition("dali_songxin",time-2);
		obj = new("/d/dali/job/sxtarget");
		obj->set("startroom", target->query("startroom"));
		obj->move(environment(target));
		ob->set_temp("songxin_target_name", obj->query("name"));
		ob->set_temp("songxin_id", obj->query("id"));
	}
	ob->set_temp("songxin_area",load_object(target->query("startroom"))->query("short"));
	ob->set_temp("songxin_areab",target->query("startroom"));
	ob->set_temp("songxin_where", get_place(ob->query_temp("songxin_areab"))+ob->query_temp("songxin_area"));

	switch(random(3)) {
	 case 0:{
	   command("nod "+ ob->query("id"));
	   command("whisper "+ ob->query("id")+" 你把这封密函火速送到「"+ob->query_temp("songxin_where")+GRN"」的「"+ob->query_temp("songxin_target_name")+GRN"」手上。");
	 }
	   break;
	 case 1:{
	   command("smile "+ ob->query("id"));
	   command("whisper "+ ob->query("id")+" 我这里正好有封信，你去把它送到「"+ob->query_temp("songxin_where")+GRN"」的「"+ob->query_temp("songxin_target_name")+GRN"」手上。");
	   break;
	 }
	 case 2:{
	   command("consider");
	   command("whisper "+ ob->query("id")+" 你赶紧把它送到「"+ob->query_temp("songxin_where")+GRN"」的「"+ob->query_temp("songxin_target_name")+GRN"」手上。");
	   break;
	 }
	}
	message_vision("$N交给$n一封密函。\n",me,ob);
	ob=new("/d/dali/job/dali_letter");
	ob->set("owner",getuid(this_player()));
	ob->move(this_player());
	return "路上常有强人出没，务必小心。";
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
			case "dali":      str = "西南大理国"; break;
			case "tls":       str = "大理天龙寺"; break;
			case "tiezhang":  str = "湖南铁掌山"; break;
			case "kunlun":    str = "";break;
			case "fairyland": str = ""; break;
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
			case "thd":       str = ""; break;
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
	string room_name, start_room;

	if(!objectp(ob)
	 || ob->query("env/invisibility")
	 || ob->query("no_quest")
	 || ob->query("race") !="人类"
	 || userp(ob)
	 || ob->query("attitude")=="aggressive"
	 || ob->query("have_master")
	 || ob->query("env/wimpy")
	 || !(start_room = ob->query("startroom"))	// add by Yuj@SJ to void job NPC
	 || !objectp(room=environment(ob))
	 || room->query("no_fight") 
	 || strsrch(room_name = base_name(room), "/d/") != 0
	 || ob->query("lastroom") == room_name && start_room != room_name
	 || start_room[0..5] != room_name[0..5]
	 || strsrch(room_name, "/d/wizard/") == 0
	 || strsrch(room_name, "/d/wuguan/") == 0
	 || strsrch(room_name, "/d/death/") == 0
	 || strsrch(room_name, "/d/kunlun/") == 0
	 || sscanf(room_name, "/d/mingjiao/%*s/") == 1
	 || strsrch(room_name, "/d/dali/") == 0
	 || strsrch(room_name, "/d/tls/") == 0
	 || strsrch(room_name, "/d/shaolin/liwu") == 0
	 || strsrch(room_name, "/d/shaolin/houyuan") == 0
	 || strsrch(room_name, "/d/huashan/jiabi") == 0
	 || strsrch(room_name, "/d/shaolin/fumoquan") == 0
	 || strsrch(room_name, "/d/shaolin/xinchan") == 0
	 || strsrch(room_name, "/d/baituo/") == 0
	 || strsrch(room_name, "/d/thd/") == 0
	 || strsrch(room_name, "/d/sld/") == 0) 
	 return 0;
	return 1;
}

string ask_fangqi()
{
	object ob = this_player();
	object obj;
	int i;
	string site;

	if (!ob->query_temp("dali_songxin"))
		return RANK_D->query_respect(ob) +"你并没有领了送信的任务，说什么放弃啊？";

	ob->delete_temp("dali_songxin");
	ob->clear_condition("dali_songxin");
	ob->delete_temp("letter_steal");
	ob->delete_temp("zuji");
	ob->delete_temp("songxin_zuji");
	ob->delete_temp("songxin");
	ob->delete_temp("songxin_time");

	if(objectp(obj = present("secret letter", ob)))
		destruct(obj);
	return "既然"+ RANK_D->query_respect(ob) +"做不了，也就罢了。";
}