#include <ansi.h>
// miehuo.h
int do_miehuo(string arg)
{
	object me, ob, obj;
	object *inv;
	me = this_object();
	ob = this_player();
	inv = deep_inventory(me);
	if( ob->is_busy())
		return notify_fail("你正忙着呢。\n");
	if( ob->is_fighting())
		return notify_fail("你正在战斗中没有手能去灭火。\n");
	if( !ob->query_temp("done", 1) )
		return notify_fail("你无聊不无聊呀！\n");
	if( !sizeof(inv))
		return notify_fail("炉子里面什么东西也没有灭什么火？\n");
	if( me->query("marks/open") )
		return notify_fail("炉子正开着呢，瞎灭什么火？\n");
	message_vision("$N把丹炉内的柴火渐渐地熄灭了。\n", ob);
//	remove_call_out("do_drug");
	remove_call_out("do_drug1");
//	call_out("do_drug", 3 , ob);
	call_out("do_drug1", 3 , ob);
	ob->delete_temp("aoyao");
	me->delete("marks/doing");
	ob->start_busy(5);
	return 1;

}
/*
void do_drug()
{
	int i, j, k, m;
	object obj, *inv;
	object me = this_object();
	object ob = this_player();
	j = 0;
	k = 0;
	m = 0;
	inv = deep_inventory(me);

	if( sizeof(inv))
	{
		for(i=0; i<sizeof(inv); i++)
		{       
			printf("enter test.\n");
			if( inv[i]->name() == HIC"川贝"NOR) 
			{       
				j = j+1;
			 }
			if( inv[i]->name() == HIW"生地"NOR) 
			{
				k = k+1;
			 }
			 if( (int)ob->query_temp("done", 1) == 1)
			 {
			 	m = 1;	
			 }
		}

		if(  sizeof(inv) != 3  
		||  j != 2 
		||  k != 1
		||  m != 1)
		{
			for(i=0; i<sizeof(inv); i++)
			{     destruct(inv[i]);    }
                        obj=new("/d/drug/chuanbei");
		        obj->move(me);
			ob->delete_temp("done");
			}
		else {
			for(i=0; i<sizeof(inv); i++)
			{      destruct(inv[i]);   }
		 	obj=new("/d/drug/jinchuang");
		       	obj->move(me);
			ob->delete_temp("done");
       		}
	}
	return;
}
*/
void do_drug1()
{
	int i, j, k, m, o, p;
	object obj, *inv;
	object me = this_object();
	object ob = this_player();
	j = 0;
	k = 0;
	m = 0;
	inv = deep_inventory(me);

	if( sizeof(inv))
	{
		for(i=0; i<sizeof(inv); i++)
		{       
			printf("enter test.\n");
			if( inv[i]->name() == HIG"何首乌"NOR) 
			{       
				j = j+1;
			 }
			if( inv[i]->name() == HIY"菊梗"NOR) 
			{
				k = k+1;
			 }
			if( inv[i]->name() == HIC"田七"NOR)
			{
				o = o+1;
			 }
			if( inv[i]->name() == HIY"雄黄"NOR)
			{
				p = p+1;
			 }
			 if( (int)ob->query_temp("done", 1) == 1)
			 {
			 	m = 1;	
			 }
		}

		if(  sizeof(inv) != 4  
		||  j != 1 
		||  k != 1
		||  o != 1
		||  p != 1
		||  m != 1)
		{
			for(i=0; i<sizeof(inv); i++)
			{     destruct(inv[i]);    }
                        obj=new("/d/drug/tianqi");
		        obj->move(me);
			ob->delete_temp("done");
			}
		else {
			for(i=0; i<sizeof(inv); i++)
			{      destruct(inv[i]);   }
		 	obj=new("/d/drug/badan");
		       	obj->move(me);
			ob->delete_temp("done");
       		}
	}
	return;
}