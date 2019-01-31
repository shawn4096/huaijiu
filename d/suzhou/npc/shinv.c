// shinv.c ��Ů

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("��Ů", ({ "shi nu", "nu", "waiter" }) );
        set("gender", "Ů��" );
        set("age", 22);
        set("long",
                "һ���������ɣ������������ݡ���������΢ʾ�⣬���ȥ�Ӳ赹ˮ��\n");
        set("combat_exp", 3800);
        set("attitude", "friendly");
        set("vendor_goods", ({
            (["name":__DIR__"obj/mitao","number":15]),
            (["name":__DIR__"obj/xiangcha","number":15]),
            (["name":__DIR__"obj/dawancha","number":10])
                
        }));
        setup();
}

void init()
{       
        object ob; 
        mapping myfam; 

        ob = this_player();

        ::init();
    if (base_name(environment()) != query("startroom")) return;
        if( interactive(ob) && !is_fighting() ) {
                if ( (myfam = ob->query("family")) 
                && myfam["family_name"] == "ؤ��" 
                && ob->query("gb_bags") < 2 )
                {
                        remove_call_out("saying");
                        call_out("saying", 0, ob);
                }
                else
                { 
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
        }

        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        switch( random(2) ) {
                case 0:
                        say( "��ŮЦ��˵������λ" + RANK_D->query_respect(ob)
                                + "�������ȱ��裬ЪЪ�Ȱɡ�\n");
                        break;
                case 1:
                        say( "��Ů˵������λ" + RANK_D->query_respect(ob)
                                + "����������\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n��Ů���һ���������Ҫ���Ľ�����ʲ�᣿ ���ҹ���ȥ��\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

    ob->move("/d/suzhou/nandajie1");
        message("vision","ֻ����ƹ����һ����" +  ob->query("name") +
                "���˴Ӳ����һ�����˳������Ǳ���״���ӿ��ˡ�\n", environment(ob), ob);
}

