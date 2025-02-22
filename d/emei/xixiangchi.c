// Room: /d/emei/xixiangchi.c

inherit ROOM;
#include <ansi.h>
#include <command.h>
string look_chi();

void create()
{
	set("short",HIW "洗象池边" NOR);
	set("long", @LONG
洗象池原只是一亭，亭前有一个石砌的小池(pool)，池边不远就是危岩。
洗象池寓于一片冷杉林中，有若白云深处的仙山琼阁。若是云收雾敛、碧空万
里、月朗中天时，便觉万籁俱寂，清光无限，宛若身在天宫，彻体生凉。这正
是著名的「象池池夜」。由此向南上攀，便至雷洞坪，东下至莲花石。
LONG
	);
	set("outdoors", "峨嵋山");
	set("item_desc",([	    
	    "pool" : (: look_chi :),
	]));
	set("exits", ([ 
	  "eastdown" : __DIR__"zuantianpo2",
	  "southup" : __DIR__"lingyunti",
	  ]));

	setup();
}

void init()
{
	add_action("do_jump", "xi");
	add_action("do_halt", "halt");
}

int do_halt(string arg)
{
	object me = this_player();

	if (!me->is_busy() && !me->is_fighting())
		me->add_busy(2);
	return 0;
}

int do_jump(string arg)
{
	int i, j;
	object me, room, *ob, *inv;
	me = this_player();
	if ( me->query("gender") == "男性" ) {
	    tell_object(me, "你一个大老爷们做那些事情干什么？\n");
	    return 1;
	}
	if (!(room = find_object(__DIR__"chi")))
	      room = load_object(__DIR__"chi");
	ob = all_inventory(room);
	j = sizeof(ob);

     if(!living(me) ) return 0;
     if (me->is_busy() || me->is_fighting())
	return notify_fail("你正忙着哪！\n");

     if( !arg || arg == "" || arg != "pool" )
	return notify_fail("你要干什么？\n");
	
     if((me->query_encumbrance()*20) > me->query_max_encumbrance())
	return notify_fail("你身上的东西太多了！\n");

     inv = all_inventory(me);
       for (i = 0; i < sizeof(inv); i++){
	       if(!inv[i]->query("no_drop"))
		  DROP_CMD->do_drop(me, inv[i]);
	       else if(inv[i]->query("equipped"))
		   inv[i]->unequip();
	       else
		  tell_object(me, "你将"+inv[i]->name()+"用衣物仔细包好。\n");	       
		}

	tell_object(me, GRN "你走到池边，除去衣物，便要跳进洗象池。\n"NOR);
	tell_room(environment(me), me->name()+"转身走到池边，好象是要跳进池里游水去。\n", ({ me }));
       if(j>0){
		if(j>1) {
			write(HIR"你突然发现池水中有人，而且还不止一个，你连忙退了回来。\n"NOR);
			return 1;
		}
		tell_object(me, "你突然发现池水中有人！\n");
		for(i=0; i<sizeof(ob); i++) {
			if(!living(ob[i])) continue;
			if(me->query("gender") == ob[i]->query("gender")){
				if(me->query("gender") == "女性")
					tell_object(me, "定眼一看，原来也是个女子。你轻轻一笑，纵身跳下水去。\n");
				if(me->query("gender") != "女性")
					tell_object(me, "定眼一看，对方不是女子。你深深叹了口气，纵身跳下水去。\n");
				me->move(__DIR__"chi");
			} else {
				tell_object(me, "定眼一看，原来对方是位。。。。你脸上一红，连忙穿上衣服退了回来。\n");
				tell_room(environment(me), me->name()+"转身走到池边，顿了一顿，又退了回来。\n", ({ me })); 
			}
		}
		return 1; 
	} 
	me->move(__DIR__"chi");
	return 1;
}

void kan_pool(object me, object room)
{
    int i, j;
    object *ob;

	if (!me || !room)
		return;
    ob = all_inventory(room);
     j = sizeof(ob);
    if (j>0){
	if (me->query("gender") == "女性")
	    return;
	tell_object(me, HIY "结果发现池中有人在裸身游水！你远远看着那模糊的雪白背影，不禁呆了。。。\n"NOR);
	if (!wizardp(me))
		tell_room(environment(me), HIY +me->name()+"突然两眼发直，张大了口，口水滴嗒滴嗒直往外流。\n"NOR, ({ me }));
	for(i=0; i<sizeof(ob); i++) {
	  if(!living(ob[i])) continue;
	  tell_object(ob[i], HIR"\n你不经意一回头，发现有人鬼鬼祟祟在池边偷看！\n"NOR);
	  ob[i]->set_temp("looked", 1);
	  if(ob[i]->query("gender") == "女性"){
	     tell_object(ob[i], HIR"你血气上冲，顿时感到一阵旋晕！\n"NOR);	     
	    if(ob[i]->query("jing")>=100)
		ob[i]->add("jing",-100);
	 else
	     ob[i]->unconcious();
	  ob[i]->set_temp("apply/short", ({ob[i]->name()+"("+ob[i]->query("id")+")"HIR" <全裸> "NOR}));	      
	 } else{
	  tell_object(ob[i], "\n你虽不以为意，但已经没有兴趣再继续游水了。\n");
	  ob[i]->force_me("halt");     
	  }
	}
     return;
     }
   return;
}

string look_chi()
{
    object me, room;
    me = this_player();
    if (!(room = find_object(__DIR__"chi")))
	  room = load_object(__DIR__"chi");

	if (me->is_busy())
		return "你正忙着呢。\n";
	if (!wizardp(me)) {
		message_vision("$N悄悄转到池边，伸长脖子往池里望去。\n", me);
		me->start_busy(30);
	}
	"/cmds/std/look.c"->look_room(this_player(), room);
	remove_call_out("kan_pool");
	call_out("kan_pool", 1, me, room); 
	return "";
}

int valid_leave(object me, string dir)
{
 if (dir == "southup" && (int)me->query_skill("dodge", 1) < 101 ) {
      me->improve_skill("dodge",(int)me->query("dex"));
      me->receive_damage("jingli",  (int)me->query("dex"));
      return 1; 
      }     
      return ::valid_leave(me, dir);
} 
