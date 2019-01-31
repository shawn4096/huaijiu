// yang.c ���ϰ� 
inherit NPC;
inherit F_VENDOR;
void create()
{
        set_name("���ϰ�", ({ "li laoban", "li" }));
        set("title", "�ӻ����ϰ�");
        set("shen_type", 1);

        set("gender", "����");
        set("age", 45);
        set("long",
                "���ϰ������������ĺ����ˣ����˼�ʮ���С������\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ({
           (["name":__DIR__"obj/changjian","number":10]),
           (["name":__DIR__"obj/gangdao","number":15]),
           (["name":__DIR__"obj/mabudai","number":15]),
           (["name":__DIR__"obj/beixin","number":20]),
           (["name":__DIR__"obj/fire","number":15]),
           (["name":__DIR__"obj/zhubang","number":25])
                
        }));
        
        setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

