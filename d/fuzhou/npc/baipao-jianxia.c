// /d/xiangyang/npc/baipao-jianxia.c

inherit NPC;

void create()
{
        set_name("���۽���", ({"baipao jianxia", "baipao", "bai", "jianxia", "xia"}));
        set("long", "����һ�������۵Ľ��ͣ���Ϊ�����Ͷ����ƣ���������Զ��������˫�۾������񣬾������̡�\n");

        set("gender", "����");
        set("attitude", "peaceful");

        set("age", 55);
        set("shen", 6500);
        set("str", 30);
        set("int", 20);
        set("con", 23);
        set("dex", 20);
        set("max_qi", 900);
        set("max_jing", 700);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiaji", 100);
        set("combat_exp", 650000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("sword", 120);
        set_skill("parry", 120);

        setup();
//        add_money("gold", 10);
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/fuzhou/obj/whitecloth")->wear();
}
