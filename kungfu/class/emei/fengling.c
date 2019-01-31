#include <ansi.h>
inherit F_MASTER;
inherit NPC;

string ask_emjiuyin();

void create()
{
       set_name("����ʦ̫", ({
               "fengling shitai",
               "fengling",
               "shitai",
       }));
       set("long","�����Ƕ����ɵڶ��������˷���ʦ̫�ˡ�\n"
	"����Ŀ���飬����Ѱ������һ�㣬�벻��һ˿����֮����\n"
       );

       set("gender", "Ů��");
       set("attitude", "friendly");
       set("unique", 1);
       set("per", 30);
       set("class", "bonze");
       set("age", 80);
       set("shen", 20000);
       set("str", 26);
       set("int", 30);
       set("con", 29);
       set("dex", 30);
       set("max_qi", 6700);
       set("max_jing", 6000);
       set("eff_jingli", 3500);
       set("neili", 15000);
       set("max_neili", 14000);
       set("jiali", 100);
       set("combat_exp", 2800000);
        

       set_skill("dacheng-fofa", 200);
       set_skill("linji-zhuang", 200);
       set_skill("jieshou-jiushi", 280);
       set_skill("huifeng-jian", 280);
       set_skill("sixiang-zhang", 280);
       set_skill("yanxing-daofa", 280);
       set_skill("hand", 280);
       set_skill("literate", 150);
       set_skill("strike", 280);
        set_skill("linji-jianzhen", 200);
       set_skill("sword", 280);
       set_skill("blade", 280);
       set_skill("parry", 280);
       set_skill("dodge", 280);
       set_skill("force", 200);
       set_skill("anying-fuxiang", 280);
       
       map_skill("force", "linji-zhuang");
       map_skill("sword", "huifeng-jian");
       map_skill("blade", "yanxing-daofa");
       map_skill("parry", "jieshou-jiushi");
       map_skill("dodge", "anying-fuxiang");
       map_skill("strike", "sixiang-zhang");
       map_skill("hand", "jieshou-jiushi");
       prepare_skill("hand", "jieshou-jiushi");

       set("inquiry", 
                ([
			"�ں�" : (: ask_emjiuyin :),

]));

       set("chat_chance_combat", 40);
       set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :),
                (: perform_action, "sword.liaoyuan" :),
                (: perform_action, "hand.foguang" :)
        }));
       create_family("������", 2, "ǰ����");

       setup();
       set_temp("apply/armor", 60);
       set_temp("apply/damage", 40);
       set_temp("apply/attack", 50);
       set_temp("apply/dodge", 40);
       if(random(2)==1)
       		carry_object(BINGQI_D("gangjian"))->wield();
       UPDATE_D->get_cloth(this_object());
}
void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }       
     
}
void greeting(object me)
{
        int shen;
        if(!me) return;
        shen = me->query("shen");
        if(shen <= -200000 && me->query("family/family_name") == "������"){
        	command("chat* smash "+me->query("id"));
        	command("say ���������������а�����ӽ������㲻���Ƕ��ҵ����ˣ�");
        	command("expell " + me->query("id"));
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "������"){
		command("look "+me->query("id"));
		command("say �ҿ����������������а��������ǲ�������������ʲô���£�");
	}
	else command("say �����ӷ�");
}
int accept_object(object me, object ob)
{

	if( me->query("family/family_name") == "������"
	&& ob->query("id") == "zhi huan" && me->query_temp("marks/pass_yitian")) {
		if(!(me->query_temp("marks/get_ring"))) {
			command("say ��öָ���ǴӺζ������ߣ���ƭ���ᣬû��ô���ף�");
			command("consider " + me->query("id"));
			command("say �������ɣ�");
			kill_ob(me);
			return 1;
		}
		command("say �ðɣ���Ȼ������ָ���������ң�������ʸ���������²������ˡ�\n");
		me->delete_temp("marks/pass_yitian");
		me->delete_temp("marks/get_ring");
		me->set_temp("bai_feng",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	}

	if( me->query("family/family_name") == "������"	&& ob->query("id") == "yu zhuo" ) {
		if(!(me->query_temp("marks/��"))) {
			command("say ��֧�������ǴӺζ������ߣ���ƭ���ᣬû��ô���ף�");
			command("consider " + me->query("id"));
			command("say �������ɣ�");
			kill_ob(me);
			return 1;
		}
		command("say �ðɣ���Ȼ�Ѻ����������ң����Ҿͽ��ں�֮���������㡣\n");
		me->delete_temp("marks/��");
		tell_object(me, HIY "���ڷ���ʦ̫�Ľ̵��£��ɹ�������֮���ں����ټ�ʮ��ׯ�����¡��־�֮�С�\n" NOR);
		me->set("emjiuyin",1); 
		remove_call_out("destroying");
		call_out("destroying", 1, me, ob);
		return 1;
	} 
	return 0;
}
void attempt_apprentice(object ob)
{
        object me; 
        mapping ob_fam, my_fam;
        string name, new_name;

        me = this_object();
        my_fam  = me->query("family");
        name = ob->query("name");
        if (!(ob_fam = ob->query("family")) || ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }
        if ( (string)ob->query("class")!="bonze" && ob_fam["family_name"] == "������") 
        {
                command("say " + RANK_D->query_respect(ob) + "���׼ҵ��ӣ����ܰ�����������ѧ�ա�");
                return;
        }

        if ( !ob->query_temp("bai_feng"))
        {
         command("say " + RANK_D->query_respect(ob) + "����û���õ�����ָ�������ܰ�����Ϊʦ��");
         return;
        }       
        if ( ob_fam["generation"] == (my_fam["generation"] + 1)) 
        {
         command("say ͽ�����㹦�����������?\n");
         ob->delete_temp("bai_feng");
         return;
         } 
        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
           if ( ob->query_temp("bai_feng") )
           {
                ob->delete_temp("bai_feng");
                command("chat ���ᴹ��֮�꣬�յõ�һ���²����ˣ����ǿ�ϲ�ɺ� !");
                name = ob->query("name");
                new_name = "��" + name[2..3];
                ob->set("name", new_name);
                command("say �ӽ��Ժ���ķ�������" + new_name + "����ϲ���Ϊ���ֱ�����֮һ !");
                command("recruit " + ob->query("id"));
                return;
                }
            command("say ��û������ָ�����Ҳ��ܰ��²����㡣\n");  
            return;
         }
          command("say ��౲���ϣ�����Խ����ʦ��\n");
          return;
        }  

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

string ask_emjiuyin()
{
	mapping fam;
        int skill;
        skill = this_player()->query_skill("jiuyin-zhengong", 1);
 
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + 
		"�뱾��������������֪�˻��Ӻ�̸��";
	if ( skill < 120 )
		return RANK_D->query_respect(this_player()) + 
		"��ľ����湦̫��޷��ںϡ�";
	if ( present("yu zhuo", this_player()) )
		return RANK_D->query_respect(this_player()) + 
		"����ȡ�ú�����Ϊ�β����佻�����᣿";

	return "��û���õ����������᲻��Ϊ�����ںϵ����⡣";

}