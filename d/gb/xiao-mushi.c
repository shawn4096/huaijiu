// /d/gb/xiao-mushi.c СĹ��
// by Looklove Y2K 5/10

#include <ansi.h>
inherit ROOM;

void create()
{
          set("short", "СĹ��");
        set("long", @LONG
����һ��СĹ�ң�ǽ�Ϲ����˻�棬�յù������ġ�ǽ����һ�ڲ�̫���
������Լ���Կ����������峺��Ȫˮ����������һ��̯���Ĳ��ڴ����������
�����Ӹ������ռ�������ʣ��ͷ�������ǿ��ڽ�������ƴ��ߴ����˯��
LONG);
        set("resource/water", 1);
        set("sleep_room",1);
        set("no_fight", 1);
        set("exits", ([
                    "east" : __DIR__"mushizl",                
        ]));
        set("objects", ([
                FOOD_D("mantou") : 4
        ]));
        set("coor/x",100);
  	set("coor/y",70);
   	set("coor/z",-10);
   	setup();
}

void init()
{
        add_action("do_drink", "drink");
        add_action("do_get", "get");
}

int do_drink(string arg)
{
        int water, max_water;
        object me = this_player();
        
        water = me->query("water");
        max_water = me->query("str")*10 ;
        
        if (!arg) {
		if ( water < max_water ) {
            		me->set("water", water+30);
              		message("vision", me->name()+"ſ�ھ�̨���Ϻ���һ��ˮ��\n",environment(me), ({me}) );
            		write("��ſ�ھ��ߺ���һ��ˮ���о�������ˡ�\n");
                	return 1;
                }
          	else write("�����ڿڲ��ʣ��Ȳ���ˮ�ˡ�\n");
       		return 1;
       	}
	return 0;
}

int do_get(string arg)
{	
	object me = this_player();
	object ob;

	if (arg && (ob = present(arg)) && ob->id("man tou"))
	{
	 	if (present("man tou", me) || me->query("family/family_name")!="ؤ��"
		|| me->query("food") > me->query("str")*10)
		{
			write("�������и��Ͻл�����һ�����㲻�ɵ��������֡�\n");
			return 1;
		}
	}
	return 0;
}
