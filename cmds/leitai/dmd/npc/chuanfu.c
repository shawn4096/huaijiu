//chuanfu.c
#include <ansi.h>
inherit NPC;
int ask_chuhai();

void create()
{
  set_name("����",({ "chuan fu"}));
        set("long",             
                "�����Ǹոս����͵����㵺���ϴ���\n"
        );
        set("gender", "����");
        set("attitude", "friendly");
        set("no_get_from", 1);
        set("unique", 1);
        set("age", 55);
        set("per",15);
        set("shen", 0);
        set("str", 30);
        set("int", 25);
        set("con", 27);
        set("dex", 29);
        set("max_qi", 500); 
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jingli", 200);
        set("eff_jingli", 200);
        set("jiali", 10);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set("inquiry", ([
        "chuhai" : (: ask_chuhai :),
       "����" : (: ask_chuhai :),
        ]));        
        set("combat_exp", 50000);

        setup();

}

void init()
{
        object me;
        me = this_player();
        ::init();
        if(present("bao shi",me))
        {
               command("say �͹٣�����������ˡ�\n");
               command("say ���ǸϽ������ɣ�\n");
        }
}

int ask_chuhai()
{

        object me = this_player();

        message_vision("$N��$n˵�������Ϸ��һ��С�ģ�\n",this_object(),me);
        message_vision("$N����һԾ�����˿촬��\n",me);
        tell_object(me,HIC"���˿촬ת�۾ͻص��˷�ɽ�ɿڡ�\n"NOR);
        me->move("/d/foshan/dukou");
        me->delete_temp("marks/�´�������3");
        me->delete_temp("marks/�´�������4");
        me->delete_temp("marks/����");
        me->delete_temp("dmd/done");
        me->remove_all_enemy();
        me->clear_condition("dmd_time");
        me->remove_all_killer();
        return 1;
}
