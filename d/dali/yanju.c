inherit ROOM;

void create()
{
	set("short", "大理盐局");
	set("long", @LONG
这是一座结构宏伟的建筑，左右石坛上各插着一根两丈多高的旗杆，杆上
锦旗飘扬。大理境内盛产井盐，这里的盐有不少都运往中原，官府为了便于管
理, 征得盐税, 特设大理盐局, 直接听命于朝廷。入口处有些盐商在说笑。
LONG
	);

	set("exits", ([
                "west" : __DIR__"beijie5",
	]));

	set("objects", ([
	        __DIR__"npc/yanshang" : 2,
	]));

	set("coor/x",-280);
  set("coor/y",-380);
   set("coor/z",-20);
   set("coor/x",-280);
  set("coor/y",-380);
   set("coor/z",-20);
   setup(); 
}

void init()
{
     object me = this_player();
     if(me->query_temp("xuncheng")){
      me->set_temp("dali_xc/yanju",1);
      }
}
