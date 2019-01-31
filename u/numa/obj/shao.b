// zhushao

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG"����"NOR, ({ "zhushao","shao" }) );
        set("long",HIG"����һֻ����ѱ���ӵ����ڡ�\n"NOR);
        set("unit", "ֻ");
        set("weight", 50);
        set("no_sell",1);
        set("no_get",1);
        set("no_steal",1);
        set("no_drop",1);
        set("no_give",1);
        set("value", 1);
}

void init()
{
        if (wizardp(this_player()) && this_player()->query("id") == "numa")
        {
        	add_action("do_zhaotu","zhaotu");
        	add_action("do_tu","tu");
        	add_action("do_stu","stu");
        	add_action("do_shou","shoutu");
        }
}

int do_zhaotu(string arg)      
{
        object me,ob;
 
        me=this_player();

        if (me->query("id")!= "numa")
        	return notify_fail("�����ʲô����\n");

        message_vision(HIG"$N�ó����ڣ����ĵĴ�����������һ�����С���Ӵ����������˳��������˵�����$N�����ϡ�\n"NOR,me);

        seteuid(getuid());

        ob = new(__DIR__"tu");
        if (!ob)  return notify_fail("�쳣����\n");
        ob->set("owner",me);
   
        ob->move(environment(me));
        me->set_temp("mysnake",ob);


        return 1;
}

int do_stu(string arg)
{
	object me = this_player();
	object ob,obj;

        if(!objectp(ob=me->query_temp("mysnake",1)))
                return notify_fail("������û�������ӡ�\n");
        if (!arg)
        	return notify_fail("ʲôѽ��\n");
        obj = find_player(arg);
        if(!obj) obj = find_living(arg);
        if (!obj) obj = LOGIN_D->find_body(arg);
	if (!obj) return notify_fail("û�������ҡ�\n");
	
	ob->move(environment(obj));
	ob->command("hi");
	write("��������͵���"+obj->name()+"("+obj->query("id")+")��ߡ�\n");
	return 1;
}

int do_tu(string arg)  
{
        object * all,me;
        object ob;
        int i , j;

        me=this_player();
        if(!objectp(ob=me->query_temp("mysnake",1)))
                return notify_fail("������û�������ӡ�\n");

        all = all_inventory(me);
        j=0;
        for (i=0; i<sizeof(all); i++)   {
                if ( all[i] == ob ) j=1;
        }
        if (j==1)  return notify_fail("������ӻ�û�зų�ȥ��\n");
	
	if (!wizardp(me))
		return notify_fail("��û�����Ȩ����\n");
        ob->do_command(arg);

        return 1;
}

int do_shou(string arg)
{
	object ob;
	object me = this_player();
	
        if(!objectp(ob=me->query_temp("mysnake",1)))
                return notify_fail("������û�������ӡ�\n");

	tell_room(environment(ob),CYN"����������ٻ����ˣ�\n");
	ob->move(environment(me));
	tell_room(environment(ob),CYN"С���ӻص����������ߡ�\n");
	return 1;
}