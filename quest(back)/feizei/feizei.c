// feizei.c
//����(lywin)2000/5/30Ϊһ������ϵͳд��npc

#include <ansi.h>
inherit NPC;

void create()
{
	set_name("����",({ "fei zei","fei" }) );
	set("title",HIY"����ݵ�"NOR);
        set("gender", "����" );
        set("age", 33);
        set("long", 
"�����޶����ķ�����������һ��СС�������������ǲ�͵��ʲô�������֡�\n");

	set("int", 30);
	set("str", 25);
	set("con", 25);
	set("dex", 35);
        set("attitude", "aggressive");
        set("shen_type", -1);

	set("qi", 1000);
	set("max_qi", 1000);
	set("jing", 1000);
	set("max_jing", 800);
	set("neili", 800);
	set("max_neili", 1000);
	set("jiali", 20);
	set("combat_exp", 500000);
	set("score", 15000);
	set_temp("apply/attack", 60);
	set_temp("apply/defense", 60);
	set_temp("apply/damage", 40);

	set_skill("unarmed",90);
	set_skill("force", 90);
	set_skill("dodge", 90);
	set_skill("parry", 90);
	set_skill("sword", 100);
	set_skill("staff", 100);
	set_skill("literate", 80);
        set_skill("poyu-quan", 180);
        set_skill("cuff", 180);
        set_skill("sword",  180);
        set_skill("dodge",  180);
        set_skill("force",  180);
        set_skill("parry",  180);
        set_skill("literate",100);
        set_skill("zixia-gong", 180);
        set_skill("huashan-jianfa",  180);
        set_skill("huashan-shenfa",  180);
        set_skill("zhengqi-jue", 180);

        map_skill("dodge", "huashan-shenfa");
        map_skill("force","zixia-gong");
        map_skill("sword","huashan-jianfa");
        map_skill("parry","huashan-jianfa");
// 66          map_skill("strike","hunyuan-zhang");
        map_skill("cuff","poyu-quan");
// 68          prepare_skill("strike","hunyuan-zhang");
        prepare_skill("cuff","poyu-quan");

        set("chat_chance_combat",30);
        set("chat_msg_combat", ({
        (: perform_action, "sword.sanqingfeng" :),
        }));
	
        set("chat_chance", 60);
        set("chat_msg", ({
                (: random_move :),
        }) );

        setup();
        carry_object("clone/misc/cloth")->wear();
        carry_object( __DIR__ "changjian")->wield();
        carry_object( __DIR__ "lingzhi");
	add_money("gold",1);

}

void init()
{
        remove_call_out("leave");
        call_out("leave",300);
}

void leave()
{
        object ob = this_object();
        if (!ob->is_fighting()) {
                message_vision(this_object()->query("name") + "���·�ߵ��Ӳݣ������ˡ�\n" NOR,this_object());
                destruct(this_object());
                }
        else call_out("leave",30);
}
