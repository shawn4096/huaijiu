// yang.c ���ϰ� 

inherit NPC;
inherit F_VENDOR;


void create()
{
        set_name("����", ({ "shang ren", "ren" }));
        set("shen_type", 1);
        set("gender", "����");
        set("age", 25);
        set("long",
                "�����ĺ����أ����⸽�����˼�������⣬Ҳû׬������Ǯ��\n");
        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_temp("apply/damage", 15);

        set("combat_exp", 40000);
        set("attitude", "friendly");
        set("vendor_goods", ([
//                  "/d/sld/obj/shengzi" : 5,
             "/d/taishan/obj/yangjing_wan" : 2,
                "/clone/misc/fire":10,

        ]));
        
        set("chat_chance", 3);
        set("chat_msg", ({
        "����̾ϧ��˵�������ߵ����֣�����˿����ˣ������ô���˻��\n",
        "����˵�������������һȺ���ˣ����϶����ߣ��涾�ޱȣ�̫�����ˡ�\n",
        (: command("fear") :),
        }) ); 


        setup();
        carry_object("/clone/misc/cloth")->wear();
//      add_money("silver",1);
}

void init()
{
//         add_action("do_list", "list");
//         add_action("do_buy", "buy");
}
