inherit NPC;

#include <ansi.h>;
void create()
{
        object ob;
        set_name("���ŵ���", ({ "tianmen daoren", "daoren", "tianmen" }) );
        set("gender", "����");
        set("title", HIW"̩ɽ�ɵ�ʮ��������"NOR);
        set("class", "taoist");
        set("age", 45);
        set("attitude", "peaceful");
        set("unique", 1);
        set("str", 26);
        set("con", 30);
        set("dex", 30);
        set("int", 28);

        set("neili", 3400);
        set("max_neili", 3400);
        set("jiali", 30);
        set("max_qi",2200);
        set("max_jing",1200);
        set("combat_exp", 1450000);
        set("eff_jingli",2000);
        set("shen_type", 1);
        set("inquiry", ([
                "������" : "������������ͬ�ˣ����������ǰ���Ч�����ˡ���\n",
                "�������" : "�󵨣��㾡��ֱ������ʦү�����֣�\n",
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
         "���ŵ���ŭ���ɶ���������������ֻ��һʱ������������������֮λ��������˲ݲݡ����ݲݴ��ڡ�\n",
         "���ŵ���̾Ϣ�����������������ˣ����������ܴ�����Ϊ���š�\n",
         "���ŵ���ŭ�𣺡�������Ҫ���Ǿ����ո������һ\n",
        (: command("sneer") :),
        (: command("pei") :),
        }) ); 


        set_skill("sword", 160);
        set_skill("force", 160);
        set_skill("parry", 160);
        set_skill("dodge", 160);
        set_skill("cuff", 160);
        set_skill("taiji-shengong", 160);
        set_skill("taizu-quan", 160);
        set_skill("taishan-jianfa", 160);
        set_skill("qingmang-jian", 160);

        map_skill("sword", "taishan-jianfa");
        map_skill("parry", "taishan-jianfa");
        map_skill("dodge", "qingmang-jian");
        map_skill("force","taiji-shengong");
        map_skill("cuff","taizu-quan");
        prepare_skill("cuff", "taizu-quan");

        create_family("̩ɽ��", 13, "����");
        setup();
        if (clonep()) {
                ob = unew(BINGQI_D("sword/dongling_jian"));
                if (!ob) ob = new(BINGQI_D("changjian"));
                ob->move(this_object());
                ob->wield();
                carry_object("/d/wudang/obj/white-robe")->wear();
        }
}

void attempt_apprentice(object ob)
{
    command("shake");
    command("say ̩ɽ���ֵ��ӽ��������ˣ�ƶ�����ݲ�����ͽ��");
    return;
}

