// yang.c ���ϰ� 

inherit NPC;
inherit F_VENDOR;


void create()
{
        set_name("�ӻ����ϰ�", ({ "lao ban", "laoban" }));
        set("shen_type", 1);

        set("gender", "����");
        set("age", 45);
        set("long",
                "�ϰ������������������ˣ����˼�ʮ���С������\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
           (["name":__DIR__"obj/quanpu","number":15]),
           (["name":"/d/hz/npc/obj/mabudai","number": 5]),
           (["name":__DIR__"obj/beixin","number":12])
        }));
        
        setup();
        carry_object("/d/city/npc/obj/cloth")->wear();
        add_money("silver",1);
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

