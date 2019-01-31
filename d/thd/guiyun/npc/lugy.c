// lugy.c
// By jpei
// ��ͽ�� Modified by Numa 19990917
// Modified by Darken for taohua quest

inherit NPC;
inherit F_MASTER;
#include "nadir.c"

// string ask_yao1();
string ask_yao2();
int ask_quest();

object ob = this_object();
void create()
{
        set_name("½��Ӣ", ({"lu guanying", "lu", "guanying"}) );
        set("title","����ׯ��ׯ��");
        set("long", "�������޳��ۣ�����������׳����\n");
        set("gender", "����" );
        set("age", 27);
        set("attitude", "peaceful");
        set("apprentice",1);
        set("str",25);
        set("int",25);
        set("con",27);
        set("dex",26);
        set("max_qi", 1200);
        set("max_jing", 1000);
        set("eff_jingli", 1200);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 30);
        set("combat_exp", 300000);

        set_skill("force", 100);
        set_skill("bihai-chaosheng", 90);
        set_skill("dodge", 90);
        set_skill("suibo-zhuliu", 90);
        set_skill("qimen-baguazhen",100);
        set_skill("parry", 90);
        set_skill("strike", 100);
        set_skill("luoying-zhang", 90);
        set_skill("leg", 110);
        set_skill("xuanfeng-tui", 110);
        set_skill("sword", 90);
        set_skill("yuxiao-jian", 80);
        set_skill("taoism", 90);
        set_skill("literate", 100);
        set_skill("qimen-bagua", 60);

        map_skill("force", "bihai-chaosheng");
        map_skill("dodge", "suibo-zhuliu");
        map_skill("strike", "luoying-zhang");
        map_skill("leg", "xuanfeng-tui");
        map_skill("parry", "luoying-zhang");
        map_skill("sword", "yuxiao-jian");
        prepare_skill("strike", "luoying-zhang");

        set("rank_info/respect", "��ׯ��");
        set("shen_type", 1);
        set("shen", 200);
//      set("vendetta_mark", "�һ���");
        create_family("�һ���", 3, "����");
        set("class", "fighter");
//        set("yao", 10);   
        set("unique", 1);   

        set("inquiry", ([
                "name": "����½��Ӣ�����������ׯ����",
                "rumors": (: ask_quest :),
                "here": "�����ǹ���ׯ�������תת�ɣ������뵽�ͷ���Ϣ��",
                "��а": "��������ʦүѽ�����������˼Ҷ�׼���Ҳ��ܸ�����ѧ�ա�",
                "��ҩʦ": "��������ʦүѽ�����������˼Ҷ�׼���Ҳ��ܸ�����ѧ�ա�",
                "����": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "jpei": "˵����Ҳ�����������ң�������һ��Ǹ�����������",
                "�һ���": "��˵��ʦ��ס�ĵط�����ϧû��ȥ������",
                "½�˷�": "���ҵĸ��ף��������˼���ʲô����",
                "½��Ӣ": "���ң��������¡�",
                "����ׯ": "�����ǻ����Ҹ���������Ѫ�Ž������ģ�����ׯԺ�����Σ�",
                "̫��": "����ׯǰ��Զ����һ���̲����Ĵ����",
                "ҩ" : "�������ұ�����ҩ���һ������ӿ��Ե���������ȡ��",
//              "���ž۾���": (: ask_yao1 :),
//                "���ɼ�����": (: ask_yao2 :),
                  "���ɼ�����": "�ҽ����ҷ��˱����ˡ�",
                "�Ż���¶��":   "�Ż���¶�����������ޱȣ��������û��! ",
        ]) );

        setup();

        carry_object(__THD__"obj/wht-cloth.c")->wear();
}

// �˴�������ͽ
void attempt_apprentice(object ob)
{
	object me= this_object();
	mapping fam= ob->query("family");
	if( fam && ob->query("combat_exp", 1) > 10000){
		command("say ���Ѿ���"+ob->query("family/family_name")+"�ĸ����ˣ����һ����ɲ������㡣");
		return;
	}
        if ( fam && fam["family_name"] =="�һ���" && (int)ob->query("family/generation")==3){
                command("say "+RANK_D->query_respect(ob)+"�Ѿ��ǼҸ��ĵ��ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
        }
        if (fam && fam["family_name"] == "�һ���" && (int)ob->query("family/generation")==2){
                command("say "+RANK_D->query_respect(ob)+"�Ѿ�����ʦү�ĵ��ӣ�"+RANK_D->query_self(me)+"����������Ϊͽ��"); 
                return;
        }

        if (ob->query("shen") <= -200000) {
                command("say ��ʦү��ƽ�����������ˣ����������޶�����аħ���������һ��");
                return;
        }
        if (ob->query("shen") >= 200000) {
                command("say ��ʦү��ƽ�����������ˣ������������������Ĺ�������֮ͽ������һ��");
                return;
        }
// change app int from 28 -> 24
        if (ob->query_int() < 24) {
                command("say ��Ĳ���̫����ʺ�ѧ���һ������似��");
                return;
        }     
        command("look " + ob->query("id"));
        command("say �ţ����㻹�Ǹ�ѧ����ϣ��Ҿ�������ɣ�");
        command("recruit " + ob->query("id"));
        ob->set("class", "fighter");
}
        
void init()
{
        object ob = this_player();

        ::init();
        if (ob->query("family/family_name") == "�һ���" && (int)ob->query("family/generation")>2)
        {
                if ((int)ob->query("shen") <= -200000)
                {
                        message_vision("½��Ӣ��$N�ȵ����������ˣ�������ʦү���������������ң���\n", ob);
                        message_vision("½��Ӣ��$N�ȵ����ӽ���������Ҳ�����һ����ĵ����ˣ�\n", ob);
                        command("expell "+ ob->query("id"));
                        ob->set("title", "�һ�����ͽ");
                }
                else if ((int)ob->query("shen") >= 200000)
                {
                        message_vision("½��Ӣ��$N�ȵ������Ǵ����������˵������ʦү��޹���������α���ӡ�\n", ob);
                        message_vision("½��Ӣ��$N�ȵ����ӽ���������Ҳ�����һ����ĵ����ˣ�\n", ob);
                        command("expell "+ ob->query("id"));
                        ob->set("title", "�һ�����ͽ");
                }
        }
}

int ask_quest()
{
        object ob = this_player(); 
        mapping fam;
       
     if (!(fam = ob->query("family")) || fam["family_name"] != "�һ���")
        return notify_fail(RANK_D->query_respect(ob) + "��Ϊ���ǵ����ɹű�ô��\n");

     if (ob->query_temp("thd/onquest")!=4)
        return notify_fail(RANK_D->query_respect(ob) + "��Ϊ���ǵ����ɹű�ô��\n");

        command("consider");
        command("say ���������������˸�����ͷ�������澹Ȼ�����ָ�ס�");
        command("say ����һ������Ҫ���ͼ��˱���ȥ����֪��Ϊʲô��");
        command("kick");
        ob->set_temp("thd/onquest",5);
        return 1;
}

