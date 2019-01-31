// Room: /d/city/dangpu.c
#include <ansi.h>;

inherit ROOM;

mapping *special=({
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
([]),
});

void getspec();

void create()
{
	set("short", "当铺");
	set("long", 
"这是一家素以买卖公平著称的老字号当铺，一个四尺高的柜台摆在你的面\n"+
"前，柜台上摆着一个牌子(paizi)， 柜台后坐着当铺的老板，一双鬼溜溜的眼\n"+
"睛上上下下打量着你，听说这里正在大量收讫『"+HBGRN+HIG+"副本贡献点"+NOR+"』。\n"
	);
        set("no_fight",1);
	set("no_sleep_room",1);

	set("item_desc", ([
		"paizi" : "公平交易，老少无欺。\n",
	]));
	set("objects", ([
		__DIR__"npc/huang" : 1,
	]));
	set("exits", ([
         "north" : __DIR__"guangchangnan",
	]));

	set("coor/x",110);
        set("coor/y",-30);
        set("coor/z",0);
	getspec();
        setup();
}

void init()
{
	add_action( "do_exchange", "exchange" );
	add_action( "do_exchange", "duihuan" );
	add_action( "do_look", "look" );
}

void getspec()
{
	mixed *file;
	int i;
	object ob;
	string tpw;
	
	file = get_dir("/clone/spec/");

	if( !sizeof(file) ) return notify_fail("找不到任何物品 \n");
	for( i = 0; i < sizeof(file); i++ )
	{	tpw = "";
                file[i] = "/clone/spec/" + file[i];
                if( file_size(file[i]) < 0 ) continue;
		ob = new(file[i]);
		
		if(!objectp(ob)) continue;		
		if(!ob->query("credit")){
			//must dest
			destruct(ob);	
			 continue;
		}
		
		if (!ob->query("rest"))
			tpw = "无";		
		else
			tpw = "每周"+chinese_number(ob->query("rest"))+"次";	
		special[i]=([
			"value"		:	ob->query("credit"),
			"name"		:	ob->query("name"),
			"id"		:	ob->query("id"),	
			"desc"		:	ob->query("desc"),	
			"degree"	:	ob->query("degree"),
			"tpw"		:	tpw, 
			"file"		:	file[i]
			 ]);
		destruct(ob);	
	}
}


int do_look(string arg) 
{       
	object me = this_player();
	int i;
        
	if(me->is_busy()) 
		return notify_fail("你正忙着呢。\n");
        	
 
        if (arg == "paizi" ){   
	        write(query("special"));
	        write("公平交易，老少无欺。\n");
	        write("本店现在收纳“副本贡献点”，可用副本贡献点兑换的限制级宝物如下：\n");
	        write("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
	        write(sprintf("┃ %-25s  %-40s  %-10s %-12s %-6s┃\n", "宝物名称","宝物作用","可用次数","使用限制","点数" ));
	        write("┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫\n");
	        for (i=0;i<sizeof(special);i++) {
	        	 if (!special[i]["value"]) continue;
	        	 write(sprintf("┃ %-25s  %-41s %-10s %-12s "+HIY+"%-6d"+NOR+"┃\n", special[i]["name"]+"("+special[i]["id"]+")",special[i]["desc"],chinese_number(special[i]["degree"])+"次",special[i]["tpw"],special[i]["value"] ));
	        }
	        write("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
	        write("请使用（duihuan xxxx）指令来兑换获得。\n");
		return 1;
	}     
	return 0;
}

int do_exchange(string arg) 
{
	int i,j;
	object ob,me = this_player();
	
	if(me->is_busy()) 
		return notify_fail("你正忙着呢。\n");
  		
	if(!arg)
		return notify_fail("你想兑换什么。\n"); 
  		
	for (i=0;i<sizeof(special);i++)
	if (arg == special[i]["id"])  
		j=i+1;	
	if(!j)
		return notify_fail("这里没有你想兑换东西。\n");
        
        if (special[j-1]["value"]>me->query("sj_credit"))
		return notify_fail("对不起你现有的副本点数不够兑换"+special[j-1]["name"]+"。\n");
        
	ob = new(special[j-1]["file"]);
	if(!objectp(ob))
		{return notify_fail("系统错误请联系WIZ。\n");}
		
	me->add("sj_credit",-special[j-1]["value"]);
	me->add("sj_credit_used",special[j-1]["value"]);
	ob->move(me,1);    
	message_vision(sprintf("当铺老板吆喝一声：“%s兑换限制级宝物%s，消耗%s个副本贡献点。”\n",me->query("name"),special[j-1]["name"],chinese_number(special[j-1]["value"])),me);
	tell_object(me,"您目前还剩"
		+ chinese_number(me->query("sj_credit"))+"个副本贡献点，您已经累计使用了" 
		+ chinese_number(me->query("sj_credit_used")) +"个副本贡献点。\n");
	log_file( "static/CREDIT",sprintf("%s(%s) | 购买%s | 剩:%s | 用:%s | 累计:%s.\n", me->name(), me->query("id"), special[j-1]["name"],chinese_number(me->query("sj_credit")),chinese_number(special[j-1]["value"]),chinese_number(me->query("sj_credit_used"))));
        me->start_busy(1);
		
	return 1; 
}