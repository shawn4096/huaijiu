inherit NPC;

inherit F_DEALER;

void create()
{
	set_name("ҩʦ", ({ "yao shi", "yao",}));
        set("long", 
"����һλ����ḻ��ҩʦ���κ�ҩ��һ���������Ͽ��Ա�ʶ���Ǻγɷ������ġ�\n");
        set("gender", "����");
        set("age", 50);
        set("str", 20);
        set("qi", 1000);
        set("max_qi", 1000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("shen_type", 1);        
        set("combat_exp", 250);
        set("attitude", "friendly");
        set("vendor_goods", ({
                __DIR__"obj/xiaojindan",
                __DIR__"obj/jindan",
                __DIR__"obj/yangjing",
                __DIR__"obj/xiaohuandan",
                __DIR__"obj/dahuan-dan",
        }));

        setup();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}


