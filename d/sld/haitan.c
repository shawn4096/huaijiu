//haitan.c
//wzfeng
#include <ansi.h>
#include <wanted.h>

inherit ROOM;
int do_kan(string arg);
int go_sld(object me);
int do_yell(string arg);

void create()
{
        set("short", "海滩");
        set("long", @LONG
这里是东海之滨的一个小海滩。放眼望去，一片无际的的茫茫
大海，远处海天一线，你隐隐看到几只海鸥在海上飞翔。海滩的四
周稀稀落落的有一些树木(tree)。
LONG
);

        set("exits", ([
				"southwest" : __DIR__"xiaolu",
            "southeast" : __DIR__"haitan1",
                
        ]));
        set("objects",([
__DIR__"npc/shangren" : 1,
]));
		set ("item_desc", ([
	"tree":"一些长得颇为茂盛得树木，你可以砍(chop)。\n",  
	]));
        set("outdoors", "taishan");
        set("coor/x",190);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}

void init()
{
	add_action("do_kan", "chop");
        add_action("do_yell", "yell");
}

int do_kan(string arg)
{
    object me,weapon1,wood;
	

	me=this_player();
	if( !arg || arg=="" ) return 0;
	if(arg!="tree")
		return notify_fail("你要砍什么？\n");

	if(!(weapon1=me->query_temp("weapon")))
		return notify_fail("你好象没有武器，拿手砍？\n");
	if(present("mu tou", environment(me)))
				{
					return notify_fail(
"这里不是已经有木头了吗？不要随意砍伐树木!!!\n");
				}


	message_vision( HIR "只见$N大喝一声，运起内力挥舞手中$n向周围的树木砍去 ....\n" NOR, me,weapon1);
	message_vision( HIR "只听“咔嚓”一声，周围的几棵大树已被$N用$n砍成几截\n"NOR,me,weapon1);
	wood = new(__DIR__"npc/obj/mutou");
	//wood->move(__FILE__);
        wood->move(environment(me));

        return 1;
}

int go_sld(object me)
{
	object hc;
	string str ="师兄";
		
	if(!objectp(hc=find_object(__DIR__"hc1")))
		hc=load_object(__DIR__"hc1");
		if(hc->query_temp("curstatus",1)=="run") {
			if(!objectp(hc=find_object(__DIR__"hc2")))
				hc=load_object(__DIR__"hc2");
				if(hc->query_temp("curstatus",1)=="run") {
					if(!objectp(hc=find_object(__DIR__"hc3")))
						hc=load_object(__DIR__"hc3");
						if(hc->query_temp("curstatus",1)=="run")
							return notify_fail("你喊了几声，却什么事也没有发生。\n");
                        }
                }
	if(me->query("gender")=="女性") str="师姐";
	message_vision(CYN"一位小童走过来对$N鞠了一躬说道：这位"+str+"要回神龙岛么？我在这里等你多时了。\n" NOR,me);
	message_vision(CYN"只见一艘大船已经驶进海口，$N慢慢走了进去。\n" NOR,me);	
	me->move(hc);
	hc->set_temp("curstatus","run");
	return 1;
}

int do_yell(string arg)
{
	object room, me;
	me = this_player();

	if ( (arg == "洪教主洪福齐天" || arg == "洪教主寿与天齐") && me->query("family/family_name")=="神龙教" ) {
		if ( is_wanted(me) ) return 0;
		else return go_sld(me);
	}

	arg = "哇";
	if (me->query("age") < 16  )
		message_vision("$N使出吃奶的力气喊了一声：“" + arg + "”\n", me);
	else if (me->query("neili") > 500)
		message_vision("$N吸了口气，一声“" + arg + "”，声音中正平和地远远传了出去。\n", me);
	else
		message_vision("$N鼓足中气，长啸一声：“" + arg + "！”\n", me);
	
	return 1;
}