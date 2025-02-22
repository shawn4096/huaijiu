//  xiao.c

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("萧老板", ({ "xiao laoban", "xiao", "laoban" }));
        set("shen_type", 1);

        set("gender", "男性");
        set("age", 40);
        set("long", "这位老板显然养尊处优，脸蛋和手掌都肥肥胖胖的。\n");
        set_skill("unarmed", 25);
        set_skill("dodge", 22);
        set_temp("apply/damage", 20);

        set("combat_exp", 9000);
        set("attitude", "friendly");
        set("vendor_goods", ({
           (["name":__DIR__"obj/xiao","number":23]),
           (["name":__DIR__"obj/pipa","number":14]),
           (["name":__DIR__"obj/yqin","number":16]),
           (["name":__DIR__"obj/dongbula","number":10])
        }));
        
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

