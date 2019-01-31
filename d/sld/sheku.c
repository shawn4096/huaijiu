// sheku.c
// �߿�
inherit ROOM;
void create()
{
	set("short","�߿�");
	set("long",@long
�������궾���������ȳ��˱ǣ���ض����ִ��ֳ��Ķ��ߺ�һ�ѶѰ׹ǣ�
ʱ���з��񱻶���Ѭ�裬��������Ϊ���ߵ���ʳ��Ⱥ��֮��Ļ�������Ҳ��
�ҳ��㷹��ֻ����Щ�书��ǿ���ö����ֲ��ܴ��������롣�˴�����û��ʲ
ô��·������Ե�������(go)����
long);
	/*set("exits",([
	    "northwest" : __DIR__"treen2",
          "southwest" : __DIR__"trees2",
          "east" : __DIR__"sande",
]));*/
set("objects",([
__DIR__"npc/shenlong": 1,
__DIR__"npc/dushe2" : 4,
]));
	set("outdoors", "������");
        set("coor/x",510);
  set("coor/y",430);
   set("coor/z",-100);
   setup();
}
	    	
void init()
{
     object me;

     me=this_player();
     if(userp(me) && me->query_skill("poison",1)<100)
         me->apply_condition("sl_poison", (5-((int)me->query_skill("poison",1))/20)*10);  
     add_action("do_go", "go");
     add_action("do_bo", "bo");
}

int do_bo(string arg)
{
     object me;
     object bg;
     object she;
     object * ob;
     int i,j;

     me = this_player();
       
     if(!living(me) ) return 0;
     if (me->is_busy() || me->is_fighting())
     	return 0;
     if(arg!="�׹�")
	return 0;
     if(random(10)<2)
     {
	if(objectp(bg=unew("/d/sld/npc/obj/baogou")))
	{
		tell_room(this_object(),"��Ȼ��ʲô������һ�Ѱ׹��е��˳�����\n");
		bg->move(this_object());
	}
     }
     else if(random(10)>6)
     {
	ob = all_inventory(this_object());
	j=0;
	for(i=0;i<sizeof(ob);i++)
	{
		if(ob[i]->query("id")=="shenlong")
			j=j+1;
	}
	if(j>=5)
		return 0;
	tell_room(this_object(),"ͻȻ�Ӱ׹�����ܳ�һ���ȸղŸ��Ӵֵľ��ߣ�\n");
	she=new("/d/sld/npc/shenlong");
	she->set("combat_exp", 500000+random(300001));
	she->set("max_qi",6000+random(4001));
        she->set("max_jing",6000+random(4001));

	she->set_temp("apply/attack", 80+random(21));
	she->set_temp("apply/defense", 500+random(501));
	she->set_temp("apply/damage", 80+random(21));
	she->set_temp("apply/armor", 500+random(501));
 	she->move(this_object());
    }
    else
	return 0;
    return 1;
}

int do_go(string arg)
{
     object me;

     me = this_player();
       
     if(!living(me) ) return 0;
     if (me->is_busy() || me->is_fighting())
        return notify_fail("����æ���ģ�\n");

     if( !arg || arg == "" || (arg != "west" && arg != "east" && arg != "north" && arg != "south" ))
        return notify_fail("��Ҫ������ȥ��\n");
     if(random(10)>=5)
         me->move(__DIR__"treen1");
     return 1;
}
