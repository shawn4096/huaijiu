#include <ansi.h>

inherit ITEM;

void create()
{
        set_name("С����", ({ "da huandan","huandan" }) );
        set("long", "һ���õ������Ƶ�С������\n");
        set("unit", "��");
        set("weight", 90);
        set("value", 10000);
}

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        object ob;
        if( !id(arg) ) return 0;
        
        ob=this_player();
        if( living(this_player()) ==0 ) return 0;
        ob->set("jing",(int)ob->query("eff_jing"));
        ob->set("qi",(int)ob->query("eff_qi"));


        write("������һ��С���������ü�������һɨ���գ�\n");

        message("vision", HIY + ob->name() + 
"����һ��С����,����һˬ.\n"+NOR,
                environment(ob), ob);
        destruct(this_object());
        return 1;
}