// xiaoer2.c �Ƶ�С��

inherit NPC;
inherit F_VENDOR;

void create()
{
        set_name("��С��", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "����" );
        set("age", 22);
        set("long",
                "��λ��С����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
        set("combat_exp", 3800);
        set("attitude", "friendly");
        set("rank_info/respect", "С����");
        set("vendor_goods", ({
           (["name":__DIR__"obj/lingbai-xiaren","number":20]),
           (["name":__DIR__"obj/yingtao-huotui","number":20]),
           (["name":__DIR__"obj/dongsun-tang","number":20]),
           (["name":__DIR__"obj/kaoya","number":15]),
           (["name":__DIR__"obj/jiudai","number":18]),
           (["name":__DIR__"obj/baozi","number":20])
         }));
        set("inquiry", ([
                "name" : "���Ҳ��ң�С�Ľ�������һֱ�����ݳ���Ĵ���¥��\n",
                "rumors" : "�����˵������һ�����˺ӣ���ͬ�˴���Ƿ��㣬�����̵�����֪�����¡�\n",
                "here" : "�����������¥�������ݳ������ľ�¥�ˡ�\n",
                ]) );
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
                        say( "��С��Ц�����˵������λ" + RANK_D->query_respect(ob)
                                + "�������ȱ��裬ЪЪ�Ȱɡ�\n");
                        break;
                case 1:
                        say( "��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
                                + "����������\n");
                        break;
        }
}

void saying(object ob)
{
        if (!ob || environment(ob) != environment()) return;

        say("\n��С�����һ���������Ҫ���Ľ�����ʲ�᣿ ���ҹ���ȥ��\n\n");
        remove_call_out("kicking");
        call_out("kicking", 1, ob);
        
}

void kicking(object ob)
{
        if (!ob || environment(ob) != environment()) return;

    ob->move("/d/suzhou/beidajie2");
        message("vision","ֻ����ƹ����һ����" +  ob->query("name") +
                "���˴Ӵ���¥��һ�����˳������Ǳ���״���ӿ��ˡ�\n", environment(ob), ob);
}

