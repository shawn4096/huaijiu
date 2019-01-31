// cool 980310
// duan1.c
// Modify By River 98/11
//COOL@SJ,990828
inherit NPC;
inherit F_MASTER;
#include <ansi.h>
string ask_join();
string ask_duan();
string strike();
string fenglu();
string ask_save();
void create()
{
	set_name("������", ({ "duan zhengchun", "duan", "master" }) );
	set("title", "������");
	set("nickname","������ү");
	set("gender", "����" );
	set("age", 44);
	set("str", 22);
	set("con", 23);
	set("dex", 23);
	set("int", 25);
	set("per", 28);
	set("attitude", "friendly");

	set("max_qi", 3000);
	set("max_jing", 1800);
	set("eff_jingli", 1800);
	set("neili", 3000);
	set("qi", 3000);
	set("jingli", 1800);
	set("max_neili", 3000);
	set("jiali", 50);

	set("rank_info/respect", "������ү");
	    create_family("������", 13, "�׼ҵ���");

	set("long",
	"�������Ǹ��൱�ߴ�����������������Ǹ����������ҵ�������ʿ��Ⱥ��\n"
	"���Ų²�����ǰ����������ŵ������˾��Ǵ�����ү��\n");

	set("combat_exp", 1100000);
	set("score", 50000);

	set("chat_chance_combat", 30);
	set("chat_msg_combat",({
	 (: perform_action, "sword.fenglei" :),(: exert_function, "qi" :)
	}));

	set_skill("parry", 150);
	set_skill("dodge", 150);
	set_skill("force", 150);
	set_skill("cuff", 150);
	set_skill("literate", 120);
	set_skill("sword", 160);
	set_skill("duanjia-jianfa", 160);
	set_skill("strike", 150);
	set_skill("qingyan-zhang", 150);
	set_skill("qiantian-yiyang", 150);
	set_skill("duanjia-quan", 150);
	set_skill("tianlong-xiang", 150);
	set_skill("finger", 150);
	set_skill("yiyang-zhi", 160);
	set_skill("buddhism", 140);
	map_skill("dodge", "tianlong-xiang");
	map_skill("parry", "qingyan-zhang");
	map_skill("sword", "duanjia-jianfa");
	map_skill("cuff", "duanjia-quan");
	map_skill("force", "qiantian-yiyang");
	map_skill("strike", "qingyan-zhang");
	map_skill("finger", "yiyang-zhi");
	prepare_skill("strike","qingyan-zhang");
	prepare_skill("cuff","duanjia-quan");

	set("inquiry", ([
	    "����" : (: ask_duan :),
	    "name": "���������Ҿ��Ƕ��������ѵ����������������ĺ��ӣ�",
	    "here": "�����������������",
	    "������" : "���������Ҷμ���ѧ�����֮�أ���������������¿ɲ�����ô���׵�.",
	    "������" : (: ask_join :),
	    "��������" : (: ask_join :),
	    "�Ʒ���Ҫ" : (: strike :),
	    "���Ʒ�" : (: strike :),
	    "ٺ»" :  (: fenglu :),
	    "Ӫ��" : (: ask_save :),
	    "���" : (: ask_save :),

	]));

	setup();
	carry_object("/d/dali/npc/obj/huangpao")->wear();
	carry_object("/clone/weapon/gangjian")->wield();
}

string strike()
{
	mapping fam = this_player()->query("family");
	object ob;
	if(!fam || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+"�뱾��������������֪�˻��Ӻ�̸��";
	if(this_player()->query_skill("strike",1) > 30)
	   return "����Ʒ��Ѿ���һ�������ˣ��Ȿ�����ûʲô�ã�����������ĵ��Ӱ�";
	ob = unew("/d/dali/obj/book-strike");
	if(!clonep(ob))
	   return "�������ˣ����ɵġ��Ʒ���Ҫ�����ڴ˴���";
	if(clonep(ob) && ob->violate_unique()){
	   destruct(ob);
	   return "�������ˣ����ɵġ��Ʒ���Ҫ�����ڴ˴���";
	   }
	ob->move(this_player());
	   return "�ðɣ��Ȿ���Ʒ���Ҫ�����û�ȥ�ú����С�";
}

string ask_join()
{
	object me;
	object ob;
	ob=this_player();
	me=this_object();
	if (ob->query("tls"))
	   return "���Ѿ��������³��ҵ����ˣ��ιʻ�Ҫ�ʴ��£�";
      //  if (ob->query("combat_exp") > 100000)
       //    return "��������ڴ�����Ҫ���������˲ţ��Ͳ�Ҫȥ�����³��Ұɡ�";
	if(ob->query_temp("tls_app"))
	   return "�Ҳ����Ѿ��Ƽ���ȥ������������ô����ȥ����";
	if((string)ob->query("gender") == "Ů��" )
	   return "�������书��Ҫ����֮�壬С����ɲ��հ�! ";
	if((int)ob->query_skill("qiantian-yiyang",1) < 100  )
	   return RANK_D->query_respect(ob) +"����Ǭ��һ����̫��,����ѧϰ�ߵȼ��Ĺ���!";
	if ( ob->query("dali_job") < 600)
	   return "�ҿ���Ϊ���������������Ļ���������Ŭ�����ɣ�";
	if ( ob->query_int() < 30 )
	   return "��������ѧ��£��ҿ���������ƺ������������޷������ô�ߵĹ���!";
	if( ob->query("marry"))
	   return "�㶼�Ѿ�����ˣ�Ҫȥ���ң����������ô�죿";
	ob->set_temp("tls_app",1);
	command ("say �����������ģ���λ�ֵܼ�ȻΪ�Ҵ������������ô����,������Ƽ���ȥ�����£�");
	return "�Ҽ�������һ�⣬�����͵��������˻���ʦ��������ٸ�ȥ��!";
}

string ask_duan()
{
	object ob = this_player(), obj;

        if(ob->query("lbwb/time")) {
	       if( ob->query("dali/meet_dy1") && ob->query("dali/pass") && ob->query_temp("duanyu/ok") && (time()-ob->query("lbwb/time"))>86400 ){
	               obj=new("/d/dali/obj/dodge_book");
                       obj->move(ob);
                       ob->delete_temp("duanyu/ok");
                       message_vision("\n$N����$nһ������\n", this_object(), ob);
                       command("say С����ǰ���岻�ʣ������常������ȥ�������ˡ�");
	               return ("����ǰ������һ�������ｻ��"+RANK_D->query_respect(ob)+" ��");
	               }
	       else return ("�ϴζ��"+RANK_D->query_respect(ob) +"��ȣ�����С��ҵ�ѿ��������Ƕ�л"+RANK_D->query_respect(ob) +"�ˡ�");
        }
	
/*	if( ob->query("dali/fail") >= 3)
	    return("��λ"+RANK_D->query_respect(ob) +"�������ˣ���л"+RANK_D->query_respect(ob) +"�����������ҿ����ǻ��������԰ɡ�"); */
	if( ob->query_temp("duanyu/find1")){
	    ob->set_temp("duanyu/ask",1);
	    return ("С����ǰ���Ĵ���˵��Ϻ�����°���ˣ����������跨Ӫ��������������汣��! ");
	}
	else return ("С������ѧ�䣬���ҳ��˼������ҳ����ˣ����������Ų��Ұ�! ");
}

string fenglu()
{
	object ob=this_player();
	mapping fam = ob->query("family");
	int gold = 0, fenglu;

	if (!fam || fam["family_name"] != "������")
		return "��λ"+ RANK_D->query_respect(ob) +"�����Ҵ�����ĳ����ѵ�Ҳ�����ô����ٺ»��";
	switch (fam["generation"]) {
		case 13:
			gold += 500;
		case 14:
			gold += 1500;
			break;
		default:
			return "��λ"+ RANK_D->query_respect(ob) +"�ڴ���ʱ�仹̫�̣��ȹ���ʱ������ðɡ�";
	}
	fenglu = ob->query("age") * 12 + ob->query("month");
	if (ob->query("fenglu") >= fenglu)
		return "��λ"+RANK_D->query_respect(ob) +"���²����Ѿ��ù�ٺ»�ˣ���ô�������ã�";
	gold *= ob->query_skill("qiantian-yiyang", 1);
	if (gold < 1) return "�������û��ٺ»��";
	ob->set("fenglu", fenglu);
	command ("pat " + ob->query("id"));
	message_vision("$N����$n"+MONEY_D->money_str(gold)+"��\n", this_object(), ob);
	MONEY_D->pay_player(ob, gold);
	return "�����㱾�µ�ٺ»����λ"+ RANK_D->query_respect(ob) +"�úøɰ���";
}

void attempt_apprentice(object ob)
{
	object me=this_object();
	mapping fam = ob->query("family");
	if( (string)ob->query("gender") == "Ů��" ){
		command ("say ���������书��Ҫ����֮�壬С�����ҿɲ��հ�!");
		return;
	}
	if (ob->query("tls")){
		command ("say ���Ѿ��������³��ҵ����ˣ��Ҳ����������ˣ�\n");
		return;
	}
	if( (int)ob->query_skill("qiantian-yiyang",1) < 80  ){
		command ("hmm");
		command ("say ��Ǭ��һ�������֮��ҿɲ�����?");
		return;
	}
	if(ob->query_int() < 30){
		command("say ѧһ��ָ֮�˱���������ߣ����ҿ�" + RANK_D->query_respect(ob) + "�������ƺ�������");
		return;
	}
	if ((int)ob->query("dali_job") < 300){
		command ("say �ҿ���Ϊ���������������Ļ���������Ŭ�����ɣ�");
		return;
	}
	if(fam["master_name"] == "������"){
	  command("haha");
	  command("say "+RANK_D->query_respect(ob)+"�����ֳ���ǰ��������"+RANK_D->query_self(me)+"����������Ϊͽ��");
	  return;
	}
	command("smile");
	command("say �ܺã�" + RANK_D->query_respect(ob) + "���Ŭ�������ձض��гɡ�");
	command("recruit " + ob->query("id") );
	ob->set("title","��������������ҽ�");
}

void recruit_apprentice(object ob)
{
	if( ::recruit_apprentice(ob) )
	 ob->set("class", "officer");
}

string ask_save()
{
	object ob;
	int i,j;
	i=random(5)+2;
	j=random(4)+3;
	ob=this_player();
	if ((int)ob->query("shen") < 0)
	   return ("�ҿ�" + RANK_D->query_respect(ob) +"�����а֮�����������Ĵ����һ��ļ�ϸ��");
	if ((int)ob->query("combat_exp") < 400000)
	   return ("�Ĵ���˶��Ǿ�������,"+RANK_D->query_respect(ob) +"�ƺ��书���������Ĵ�����භ��������֮�ǡ�");
	if (ob->query_temp("duanyu/find2"))
	   return ("����ô������ȥ��?ʱ����ȣ�");
	if( ob->query_temp("duanyu/ask")){
	   ob->set_temp("duanyu/step",i);
	   ob->set_temp("duanyu/steps",j);
	   ob->set_temp("duanyu/find2",1);
	   return ("��Ȼ"+ RANK_D->query_respect(ob) +"���������������绢�������ҵ�֪���������Ĵ����֮��\n"+
		   "������������������ɽ������һ��ʯ���ڣ�ֻ��·��ʮ���ն�֮ǰΪ��̽��·�ߣ�\n"+
		   "������ʧ�ü������¡�����ȥ������ȥ����ɽ·�ϵ�һ��СϪ����������\n"+
		   "��������"+chinese_number(j)+"�������"+chinese_number(i)+"�Ȼ��ᵽһ����ɽ���������Ҫ���������ˡ�\n"+
		   "������˵�������ˣ�׼��һ�£�Ϊ�˲������Է����м�Ҫ�������ж���·��С�ġ�");
	}
	else return ("�˻��Ӻ�̸��");
}

void init()
{
       object ob;
       int i;
       mapping my_fam;
       ob = this_player();
       i = ob->query_skill("liumai-shenjian",1);
       if (ob->query("family"))
       my_fam=ob->query("family");

       if (ob->query("family") && (my_fam["family_name"] == "����")){
	  ob->set("family/family_name","������");
	  if (my_fam["generation"] < 4 ){
	     ob->set("family/generation", 14);
	     ob->set_skill("buddhism",ob->query_skill("qiantian-yiyang", 1));
       }
       else {
	     ob->set("family/generation", 15);
       }
       if (ob->query_skill("liumai-shenjian",1)) {
	  ob->set_skill("yiyang-zhi",i);
	  ob->delete_skill("liumai-shenjian");
	  ob->set_skill("kurong-changong",100);
	  command ("say ������ܽӿ���ʮ��,������ѧϰ���� \n");
       }
	  command ("say ����,�����������ϲ�,������������׼ҵ�����! \n");
       }
       ::init();
}
