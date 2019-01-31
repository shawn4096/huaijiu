// NPC: /d/huashan/npc/puren.c
// Date: Look 99/03/25
// Modify By Looklove@SJ 2000/1/7

#include <ansi.h>
inherit NPC;
string ask_over();

void create()
{
        set_name("����", ({ "pu ren", "puren",}));
        set("long","һ���շ�ɨ�ص�����\n");
        set("gender", "����");
        set("age", 26);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 23);
        set("int", 23);
        set("con", 24);
        set("dex", 28);
        
        set("max_qi", 300);
        set("max_jing", 180);
        set("neili", 300);
        set("max_neili", 300);
        set("eff_jingli", 180); 

        set("jiali", 5);
        set("combat_exp", 5000);
        set("score", 50);

        set_skill("unarmed", 20);
        set("inquiry", ([
              "���" : (: ask_over :),
        ]));
        setup();
        carry_object(ARMOR_D("armor/cloth"))->wear();
}
string ask_over()
{
        int exp,pot;
        object me;
        me = this_player();
        
        if ((int)me->query("combat_exp") >= 100000)
                return "��Ȼ����ȱ��̣�������Щ�»������������������ɡ�\n";
        
        if (me->query("shen") < 1000)
                return "���ǣ�����¶�׹�, ����ǲ�������ʲô���£� "; 
        
        if (!me->query_temp("hs/kc_job")||!me->query_temp("kc_job/ok"))
                return "����ʦ�ָղ���˵��Ҫ�����Ҽ�������ȥ������ȥ��ȥ��ȥ�͸�����һ����\n";

        me->delete_temp("hs/kc_job");
        me->delete_temp("kc_job");
        me->clear_condition("job_busy");

        exp = me->query("max_pot")/2+random(20);
        pot = exp/6+random(exp/10); 
        if ( pot < 40 ) pot = 20+random(20);
                
        me->add("combat_exp",exp);
        me->add("shen",exp*3/4);
        me->add("potential",pot);
        if(me->query("potential") > me->query("max_pot"))
        me->set("potential", me->query("max_pot"));
        me->improve_skill("zixia-gong",me->query("int")*2);
        me->apply_condition("job_busy",3+random(2));
        
        message_vision("$N����������˵��������Ҫ�Ĳ���Ҷ����ˣ����ڳ����壬��Ҫ�Ļ�������ȥȡ����\n",me);
//      message_vision("$N˵��ת������ˡ�\n",me);
        tell_object(me,HIM" ��õ��ˣ�\n" + 
        chinese_number(exp) + "��ʵս����\n"+
        chinese_number(pot) + "��Ǳ�ܡ�\n"NOR);
        command("ok "+me->query("id"));
//      me->move(__DIR__"celang3");
        return "�ȶ��Űɣ�����Ҫ�õ�ʱ���Ҿ�ȥȡ��\n";
}
