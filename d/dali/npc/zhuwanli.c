//by cool 98.3.25
// ���ܺ�wd,xs jobһ������River@SJ 2000.7.19

inherit NPC;
#include <ansi.h>
string get_place(string str);
int check(object ob);
string ask_job();
string ask_fangqi();

void create()
{
	set_name("������", ({ "zhu wanli","zhu","wanli" }));
	set("title", "��������������ҽ�");
	set("gender", "����");
	set("age", 33);
	set("str", 27);
	set("dex", 26);
	set("long", "���������������ϲ���һ��������Ӣ�����ˡ�\n");
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
	     "����" : (: ask_job :),
		 "job" : (: ask_job :),
		 "fangqi" : (: ask_fangqi :),
		 "����" : (: ask_fangqi :),
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
		return RANK_D->query_respect(ob) +"���㲻�Ǳ�������ӣ��˻��Ӻ�˵��";

	if (ob->query_temp("dali_songxin"))
		return "�㲻���Ѿ��������ŵ������𣿻�����ȥ����";

	if (ob->query("job_name") == "��������")
		return "�����������������񣬻���ȥ��Ϣһ��ɡ�";

	if (ob->query_condition("dali_songxin") > 0)
		return "������ʱû�и���������ٵ�"+chinese_number((ob->query_condition("dali_songxin")+5)/6)+"��ʱ���ɡ�";

	if( ob->query_condition("job_busy"))
		return "��������æ�������������أ�";

	if (ob->query("combat_exp") < 100000)
		     return ("��Ĺ��򻹲����������ſ��Ǻ�Σ�յ��£��ҿɲ��ҽ�����������");

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (j <= 1 || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			str = environment(target)->query("short");
			if( str == "��ɮ��" 
			 || str == HIR"������"NOR
			 || str == "��շ�ħȦ" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	} 

	if( !target )
		return "��ʱû������Ҫ�ͣ����һ��������ɡ�";
	
	time = random(10)+ 25;
	ob->delete_temp("songxin_ok");
	ob->delete_temp("dali_songxin_late");
	ob->set_temp("dali_songxin",1);
	ob->set_temp("songxin_time",time);
	ob->delete_temp("songxin_zuji");
	ob->apply_condition("job_busy", time);
	ob->set("job_name", "��������");

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
	   command("whisper "+ ob->query("id")+" �������ܺ������͵���"+ob->query_temp("songxin_where")+GRN"���ġ�"+ob->query_temp("songxin_target_name")+GRN"�����ϡ�");
	 }
	   break;
	 case 1:{
	   command("smile "+ ob->query("id"));
	   command("whisper "+ ob->query("id")+" �����������з��ţ���ȥ�����͵���"+ob->query_temp("songxin_where")+GRN"���ġ�"+ob->query_temp("songxin_target_name")+GRN"�����ϡ�");
	   break;
	 }
	 case 2:{
	   command("consider");
	   command("whisper "+ ob->query("id")+" ��Ͻ������͵���"+ob->query_temp("songxin_where")+GRN"���ġ�"+ob->query_temp("songxin_target_name")+GRN"�����ϡ�");
	   break;
	 }
	}
	message_vision("$N����$nһ���ܺ���\n",me,ob);
	ob=new("/d/dali/job/dali_letter");
	ob->set("owner",getuid(this_player()));
	ob->move(this_player());
	return "·�ϳ���ǿ�˳�û�����С�ġ�";
}

string get_place(string str)
{ 
	string *place = explode(str, "/");

	str = "";
	if(place[0] == "d")
		switch(place[1]){
			case "baituo":    str = "�������ɽ";  break;
			case "hj":	str = "����ؽ�"; break;
			case "mingjiao":  str = "��������"; break;
			case "shaolin":   str = "������ɽ����"; break;
			case "songshan":  str = "������ɽ"; break;
			case "wudang":    str = "�����䵱ɽ"; break;
			case "xingxiu":   str = "�������޺�"; break;
			case "city":      str = "�������ݳ�"; break;
			case "emei":      str = "�Ĵ�����ɽ"; break;
			case "fuzhou":    str = "�Ͻ�����"; break;
			case "jiaxing":   str = "���ϼ���"; break;
			case "taishan":   str = "ɽ��̩ɽ"; break;
			case "dali":      str = "���ϴ����"; break;
			case "tls":       str = "����������"; break;
			case "tiezhang":  str = "��������ɽ"; break;
			case "kunlun":    str = "";break;
			case "fairyland": str = ""; break;
			case "gumu":      str = ""; break;
			case "chengdu":   str = "�Ĵ��ɶ�"; break;
			case "huashan":   str = "������ɽ"; break;
			case "xiangyang": str = "��������"; break;
			case "xueshan":   str = "������ѩɽ"; break;
			case "wizard":    str = ""; break;
			case "death":     str = ""; break;
			case "gaibang":   str = "ؤ��ֶ�"; break;
			case "hz":	str = "���Ϻ���"; break;
			case "village":   str = "����С��"; break;
			case "wuguan":    str = "�������"; break;
			case "thd":       str = ""; break;
			case "gaibang":   str = "ؤ��ֶ�"; break;
			case "mr":	str = "����������"; break;
			case "suzhou":    str = "�����س�"; break;
			case "sld":       str = "����������"; break;
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
	 || ob->query("race") !="����"
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
		return RANK_D->query_respect(ob) +"�㲢û���������ŵ�����˵ʲô��������";

	ob->delete_temp("dali_songxin");
	ob->clear_condition("dali_songxin");
	ob->delete_temp("letter_steal");
	ob->delete_temp("zuji");
	ob->delete_temp("songxin_zuji");
	ob->delete_temp("songxin");
	ob->delete_temp("songxin_time");

	if(objectp(obj = present("secret letter", ob)))
		destruct(obj);
	return "��Ȼ"+ RANK_D->query_respect(ob) +"�����ˣ�Ҳ�Ͱ��ˡ�";
}