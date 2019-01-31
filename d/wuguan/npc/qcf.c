// qi-changfa.c

#include <ansi.h>
#include <localtime.h>

inherit NPC;

int ask_fy();
int ask_rm();
private void set_enter_date(object ob,int date);
private int query_date(int date);

void create()
{
        set_name("戚长发", ({ "qi changfa", "qi", "changfa"}) );
        set("title", "铁索横江" );
        set("gender", "男性" );
        set("age", 45);
        set("long", "这位先生站在那里，一副神秘莫测的样子。你可以向他询问容貌或者福源的问题\n");
        set("combat_exp", 80000);
        set("unique", 1);
        set("attitude", "friendly");
        set("inquiry", ([                 
                "rumors" : "要想知道你今生的祸福荣辱，那就问我来算命吧。",
                "福源": (: ask_fy :),
                "容貌": (: ask_rm :),
                "寒雨": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "jpei": "说起来也是他创造了我，不过这家伙是个造ｑｕｅｓｔ狂。",
                "算命" : "我的价钱最公道，不多不少，只要二两银子。"
        ]) );

/*        set("chat_chance", 3);
        set("chat_msg", ({
                "戚长发吆喝道：铁嘴神算，价钱公道，相资二两白银。\n",
                (: random_move :),
                "戚长发对你说道：客倌请留步，卜个吉凶如何？\n",
        }));*/
                carry_object(ARMOR_D("cloth"))->wear();
       setup();
}

int ask_fy()
{
	object me = this_player();
        int i;
        i = me->query("kar");
        command("say 你目前的福源是" + chinese_number(i) + "。\n");
        return 1;
}

int ask_rm()
{
	object me = this_player();
        int i;
        i = me->query("per");
        command("say 你目前的容貌是" + chinese_number(i) + "。\n");
        return 1;
}