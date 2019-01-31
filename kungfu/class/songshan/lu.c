#include <ansi.h>
inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("½��", ({ "lu bo", "lu", "bo" }));
        set("nickname", "�ɺ���");
        set("long", "����һ�����������ߣ�����ɽ�����������ѽ��ε��ɺ���½�ء�\n");
        set("gender", "����");
        set("age", 46);
        set("per", 18);
        set("attitude", "heroism");
        set("shen_type", -1);
        set("str", 24);
        set("int", 23);
        set("con", 26);
        set("dex", 26);
         set("unique", 1);
        set("max_qi", 3000);
        set("max_jing", 2000);
        set("eff_jingli", 2000);
        set("jiali", 50);
        set("combat_exp", 1500000);
        set("shen", -14000);

    set_skill("force", 150);
    set_skill("hanbing-zhenqi", 150);
    set_skill("dodge", 150);
    set_skill("zhongyuefeng", 150);
    set_skill("hand", 130);
    set_skill("songyang-shou", 130);
    set_skill("parry", 150);
    set_skill("sword", 160);
    set_skill("songshan-jian", 150);
    set_skill("literate", 100);
    map_skill("force", "hanbing-zhenqi");
    map_skill("dodge", "zhongyuefeng");
    map_skill("hand", "songyang-shou");
    map_skill("parry", "songshan-jian");
    map_skill("sword", "songshan-jian");
    prepare_skill("hand", "songyang-shou");
    create_family("��ɽ��", 5, "����");
    set("chat_chance_combat", 20);
    set("chat_msg_combat", ({
                (: perform_action, "sword.feiwu" :),
                (: exert_function, "juhan" :),
        }));

        setup();
        carry_object(ARMOR_D("changpao1"))->wear();
        carry_object(BINGQI_D("changjian"))->wield();        
        add_money("gold", 1);
}

/*
void attempt_apprentice(object ob)
{
     if(ob->query_skill("songshan-qigong",1) < 90 ||
        ob->query_skill("songshan-jian",1) < 100 ||
        ob->query_skill("songyang-shou",1) < 90){
        command("say ����书��������죬�ٻ�ȥ�����ɡ�");
        return;
        }
     command("say �ðɣ��������㻹���������ϡ�");
     command("recruit " + ob->query("id"));
}
*/

