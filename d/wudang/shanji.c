// shanji.c ɽ��
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(YEL"ɽ��"NOR, ({ "shan ji", "ji"}) );
        set("race", "Ұ��");
        set("age", 5);
        set("long", "һֻ��ë�����Ĵ�ɽ����\n");
        set("attitude", "peaceful");
        
        set("limbs", ({ "ͷ��", "����", "ǰ��", "���", "β��" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("combat_exp", 500);
//      set("shen_type", 0);

//      set("chat_chance", 6);
//      set("chat_msg", ({
//              (: this_object(), "random_move" :),
//      }) );
        
        set_temp("apply/attack", 2);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 2);
        set_temp("apply/armor", 1);

        setup();
}

void die()
{
        object ob;
        message_vision("$N��ҵ������˼�����һͷ�ص��������ˡ�\n", this_object());
        ob = new(__DIR__"obj/jitui");
        ob->move(environment(this_object()));
        destruct(this_object());
}
        
