// /kungfu/class/emei/mie-jue.c
// Make by jackie 98.2

inherit F_MASTER;
inherit NPC;
#include "miejue.h"
int ask_sword();
int ask_zhou();
int ask_guo();
int ask_jiuyin();
int ask_dragon();
void create()
{
        set_name("���ʦ̫", ({
                "miejue shitai",
                "miejue",
                "shitai",
        }));
        set("long","�����Ƕ����ɵ��������������ʦ̫�ˡ�\n"
"����ò��ü�����������üëбб�´���һ��������ü��ǹ��죬����\n"
"�е��Ϸ̨�ϵĵ�����ζ����\n"
        );

        set("gender", "Ů��");
        set("attitude", "friendly");
         set("unique", 1);
        set("class", "bonze");

        set("age", 50);
        set("shen_type", 1);
        set("str", 42);
        set("int", 42);
        set("con", 42);
        set("dex", 42);
        set("max_qi", 3500);
        set("max_jing", 3500);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 100);
        set("combat_exp", 1200000);
        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "sword.mie" :)
            }));

        set_skill("dacheng-fofa", 165);
        set_skill("linji-jianzhen", 180);
        set_skill("linji-zhuang", 165);
        set_skill("jieshou-jiushi", 165);
        set_skill("huifeng-jian", 165);
        set_skill("sixiang-zhang", 165);
        set_skill("yanxing-daofa", 165);
        set_skill("hand", 165);
        set_skill("literate", 165);
        set_skill("strike", 165);
        set_skill("sword", 165);
        set_skill("blade", 165);
        set_skill("parry", 165);
        set_skill("dodge", 165);
        set_skill("force", 165);
        set_skill("anying-fuxiang", 165);
        set("inquiry",([
          "���콣" : (: ask_sword :),
          "�����澭" : (: ask_jiuyin :),
          "������" : (: ask_zhou :),
          "����" : (: ask_guo :),
          "����" : (: ask_guo :),
          "��������" : (: ask_dragon :),
          "��������" : (: ask_dragon :),
        ]) );


        map_skill("force", "linji-zhuang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-daofa");
        map_skill("parry", "huifeng-jian");
        map_skill("dodge", "anying-fuxiang");
        map_skill("strike", "sixiang-zhang");
        map_skill("hand", "jieshou-jiushi");

        prepare_skill("hand", "jieshou-jiushi");

        create_family("������", 3, "����");

        setup();
        carry_object(BINGQI_D("changjian"))->wield();
        carry_object("/d/emei/obj/shoes")->wear();
        carry_object("/d/emei/obj/cloth")->wear();
}
void init()
{
        object me, ob;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob = this_player()) && !wizardp(ob) && !is_fighting()) {
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
        	command("chat* kick2 "+me->query("id"));
        	command("say ���������������а�����ӽ������㲻���Ƕ��ҵ����ˣ�");
        	command("expell " + me->query("id"));
	}
	if(shen <0 && shen > -200000 && me->query("family/family_name") == "������"){
		command("look "+me->query("id"));
		command("say �ҿ����������������а��������ǲ�������������ʲô���£�");
	}
	else command("say ��Ĺ����չ����ˣ�");
}