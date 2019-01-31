// song.c ��Զ��

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
       set_name("��Զ��", ({ "song yuanqiao", "song" }));
       set("nickname", "�䵱����");
       set("long", 
	       "������������Ĵ���ӡ��䵱����֮�׵���Զ�š�\n"
	       "��һ���ɸɾ����Ļ�ɫ���ۡ�\n"
	       "���������ʮ������ݳ���������⡣�񵭳�ͣ���Ĭ���ԡ�\n");
       set("gender", "����");
       set("unique", 1);
       set("age", 61);
       set("attitude", "peaceful");
       set("shen", 10000);
       set("str", 29);
       set("int", 27);
       set("con", 26);
       set("dex", 26);
       set("no_get","��Զ�Ŷ������̫���ˡ�");
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
       create_family("�䵱��", 2, "����");

       set("inquiry", ([
		"�ؼ�" : (: ask_me :),
		"��Ҫ" : (: ask_me1 :),
		"����" : (: ask_me2 :),
		 "job" : (: ask_me2 :),
		"Ѳɽ" : (: ask_me2 :),
	      "fangqi" : (: ask_me3 :),
		"����" : (: ask_me3 :),
	     "abandon" : (: ask_me3 :),
		"����" : (: ask_me4 :),
		"����" : (: ask_me4 :),
		"����" : (: ask_me4 :),

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
	    command("say "+ob->name()+"���Ѿ����˰�����Ƕ����������ˣ�");
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_job_lost2");
	    ob->delete("wd/wd_bonus");
	    ob->apply_condition("job_busy", 3);
	}
	if(ob->query("wd/wd_job_lost")) {
	    command("sigh "+ob->query("id"));
	    command("say "+ob->name()+"����ô��ģ���Ȼ���Ƕ��������ˣ�");
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_job_lost");
	    ob->delete("wd/wd_bonus");
	    ob->apply_condition("job_busy", 3);
	}
	if(ob->query("wd/wd_jobok") ){
	    command("thumb "+ob->query("id"));
	    command("say �ܺã�ף���������������ȥ��Ϣ��Ϣ�ɣ�");
	    ob->add("wd_job",1);
	    count += 1;
	    ob->add("combat_exp",e);
	    ob->add("potential",p);
	    if( ob->query("family") && ob->query("family/family_name")!="�һ���")
	    ob->add("shen",shen);
	    ob->delete("wd/wd_job");
	    ob->delete("wd/wd_job_place");
	    ob->delete("wd/wd_jobok");
	    ob->delete("wd/wd_bonus");
	    if ( (int)ob->query("potential", 1) > (int)ob->query("max_pot", 1) )
	      ob->set("potential" , ob->query("max_pot", 1) );
	    tell_object(ob, GRN"������"+CHINESE_D->chinese_number(e)+"�㾭�飬"+CHINESE_D->chinese_number(p)+"��Ǳ�ܣ�����������������ˣ�\n"NOR);
	    write_file( "/log/job/wd_job",sprintf("%s %s(%s)��%d��������%d�㾭�飬%d��Ǳ�ܣ����飺%d���Ѷȣ�%d\n",
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
	   command("say ϰ��֮��Ӧ־�ڳ�����ƣ�"+RANK_D->query_respect(me)+"Ŀ¶��������Υ��ѧ֮����");
	   return 0;
	}
	::fight_ob(me);
	 return 1;
}

void attempt_apprentice(object ob)
{
       if ((int)ob->query("shen") < 10000) {
	       command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
	       command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
		       "�Ƿ����ò�����");
	       return;
       }
       command("say �ðɣ�ƶ�����������ˡ�");
       command("recruit " + ob->query("id"));
}

string ask_me()
{
       mapping fam; 
       object ob;
       if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
	       return RANK_D->query_respect(this_player()) + 
	       "�뱾��������������֪�˻��Ӻ�̸��";
       if(query("book_count2") < 1)
	 return "�������ˣ����ɵ��ڹ��ķ����ڴ˴���";
       add("book_count2",-1);       
       ob = new(__DIR__"force_book");
       ob->move(this_player());
       return "�ðɣ��Ȿ��̫��ʮ��ʽ�����û�ȥ�ú����С�";
}

string ask_me1()
{
	mapping fam; 
	object ob,song;	
	song = this_object();
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "�䵱��")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if (query("book_count1") < 1)
	   return "�������ˣ�������Ҫ�Ѿ����ڴ˴��ˡ�";
	add("book_count1",-1);	 
	ob = new(__DIR__"blade_book");
	ob->move(this_player());
	return "�Ȿ���н����ĵ���Ҫ�죬���ȥ�ú��о�һ�¡�";
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
	      return "�ߣ����������ɹţ�������ʲô��";

	if (me->query("wd/wd_job") && !me->query("wd/wd_job_place"))
	      return "���������Բ��𣬵ص�������������������ɡ�";

	if (me->query("wd/wd_job"))
	      return "�Ҳ��Ǹ���������������"+ str2 +CYN"�������ҡ���Ϳ�ȥ�ɣ�";

	if (me->query("job_name") =="�䵱����")
	      return "��������䵱�������񣬻�����ȥ��Ϣһ��ɡ�";

	if (me->query("shen") < 10000 && !wizardp(me) )
	      return RANK_D->query_respect(me) + "�����������������޷������������������";

	if (me->query("combat_exp") < 100000 )
	      return "��λ" + RANK_D->query_respect(me) + "�书δ�ɣ�����ȥ����Ĺ����ɣ�";

	if ( me->query_condition("job_busy")){
	      if (me->query("job_name")=="�䵱����")
		  return "������ʱ��û�й�������ȥ����";
		if( me->query("job_name"))
		  return "�������"+me->query("job_name")+"���񣬻�������Ϣһ��ɡ�";
		return "����æ�ű�������ء�";
	}

	if (me->query_condition("wd_job"))
	     return "������ʱû���ʺ���Ĺ�����";

	living = livings();
	for (i=0;i < sizeof(living);i++){
		j = random(sizeof(living));
		if (!j || j == sizeof(living) -1) continue;
		if(check(living[j]) ){
			target = living[j];
			objwhere = environment(target);
			str = objwhere->query("short");
			if (!sizeof(objwhere->query("exits"))
			|| str == "��ɮ��" 
			|| str == HIR"������"NOR
			|| str == "��շ�ħȦ" ) continue;
			if( get_place(base_name(environment(target)))!="" ) break;
		}
	} 

	if( !target )
		return "��ʱû��������Ҫ�������һ��������ɡ�";

	me->set("wd/wd_job",1);
	me->set("wd/wd_job_place", get_place(base_name(environment(target)))+environment(target)->query("short"));
	me->apply_condition("wd_job",40);
	me->apply_condition("job_busy",40);
	me->set("job_name","�䵱����");
	command("nod "+me->query("id"));
	ob=new(__DIR__"robber");
	ob->set_temp("target", me->query("id") );
	ob->move(objwhere);
	log_file( "job/wd_job",sprintf("%s %s(%s)��ʼ��wd job,Ŀǰʵս���飺%d\n", ctime(time()),me->name(),me->query("id"),me->query("combat_exp")));
	command("whisper "+ me->query("id")+" ��˵"+ob->query("title")+GRN+ob->query("name")+"����"+ me->query("wd/wd_job_place") +GRN"�������ң�������ȥ����Ѳ��һȦ��");
	return "���ȥ��أ�һ��С�İ���";
}

string ask_me3()
{
	object ob = this_player();

	if(ob->query("wd/wd_job")){
		ob->delete("wd/wd_job");
		ob->delete("wd/wd_job_place");
		ob->delete("wd/wd_bonus");
		return ob->name()+"����̫����ʧ���ˣ���Ȼ��ô���ɲ��ã������°ɣ�";
	}
	return ob->name()+"������û��������������Ϲ����ʲôѽ��";
}

string ask_me4()
{
	object ob;
	ob = this_player();
	if(!ob->query("wd_job")){
	    return "�Բ���"+ob->name()+"�������û������������������أ����͸ɰɣ�";
	}
	return ""+ob->name()+"�����Ѿ��ɹ��ز�����"+CHINESE_D->chinese_number((int)ob->query("wd_job"))+"��������";
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
			case "dali":      
			switch(place[2]) {
				case "daliwest":	str = "���ϴ������";	break;
				case "dalisouth":	str = "���ϴ������";	break;
				case "dalieast":	str = "���ϴ������";	break;
				case "wuliang":		str = "����ɽ";		break;
				case "dlhg":		str = "���ϴ�����ʹ�";	break;
				case "wangfu":		str = "���ϴ��������";	break;
				case "yideng":		str = "��Դ��";		break;
				case "yuxu":		str = "�����";		break;
				default : 		str = "���ϴ����";		break;
			}
			break;
			case "tls":       str = "����������"; break;
			case "tiezhang":  str = "��������ɽ"; break;
			case "kunlun":    str = "";break;
			case "fairyland": str = "��������ɽ"; break;
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
			case "thd":       str = "�����һ���"; break;
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
	 || room->query("outdoors") == "���ش��"
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
