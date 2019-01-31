#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("����", ({ "tie jiang", "tie",}));
        set("long", 
"�������ĺ�ˮ����Ц�����Ŀ�����,����ʱ������ڲ����ϵ�Ĩ���������\n");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        
        set("max_qi", 600);
        set("max_jing", 300);


        set_skill("parry", 60);
        set("vendor_goods", ({
                __DIR__"obj/gangjian",
                __DIR__"obj/armor",
                __DIR__"obj/bag",
                __DIR__"obj/bi", 
                __DIR__"obj/blade",
                __DIR__"obj/changbian", 
            __DIR__"obj/changjian",
            __DIR__"obj/dao",
            __DIR__"obj/duanjian",
            __DIR__"obj/gangdao",
            __DIR__"obj/gangzhang",
            __DIR__"obj/jiujiebian",
            __DIR__"obj/muchui",
            __DIR__"obj/tiegun",
            __DIR__"obj/zhujian",


       }));        

        setup();
}
void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "����Ц�����˵������λ" + RANK_D->query_respect(ob)
                                + "�����������������ðɡ�\n");
                        break;
                case 1:
                        say( "�����ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
                                + "����������\n");
                        break;
        }
}