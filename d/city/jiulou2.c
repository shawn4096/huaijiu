// yangzhou/jiulou2.c
// By snowman@SJ 27/05/2000

#include <ansi.h>
inherit ROOM;
string *cnumber = ({ "⑴","⑵","⑶","⑷","⑸","⑹","⑺","⑻","⑼","⑽" });

string look_juanbo();

void create()
{
    	set("short", "瘦西湖雅楼");
	set("long", @LONG
这里是雅座，文人学士经常在这里吟诗作画，富商土豪也在这里边吃喝边作交
易。这里也是城里举办喜宴的最佳场所。楼上有一阁, 从阁中往外眺望，只觉得心
旷神怡。东面就是闻名的瘦西湖, 碧波荡漾。北面是崇山峻岭，而南面可以看到白
鹿书院的后庭。这里坐了几桌客人，有文有武，还有一些围在一张卷帛(juanbo)旁
评论着什么。
LONG);
	set("objects", ([
		__DIR__"npc/shusheng" : 1,
	]));
	set("map_link_room", __DIR__"jiulou");
	set("item_desc",([
        	"juanbo" : (: look_juanbo :),
        ]));
	set("exits", ([
		"down" : __DIR__"jiulou",
	]));

	set("coor/x",80);
  set("coor/y",10);
   set("coor/z",10);
   set("coor/x",80);
  set("coor/y",10);
   set("coor/z",10);
   setup();
}

string look_juanbo()
{
	mapping artnames = "/cmds/usr/artname"->query_artnames();
      	string *key2, arg, str = "\n", *key = ({ });
      	int i, j;
      	
      	arg = "\t       ";
      	key = keys(artnames);
      	
      	if ( !sizeof(key) || sizeof(key) < 1 )
      		return "\n目前还没有关于任何人的提议。\n请推举(artname)新的外号，如果赞同现有的，也请提议一次你所赞同的外号。 \n\n";
      		
      	str = "目前有以下提议："
	+"\n┏━━━━━┯━━━━━━┯━━━━━┯━━━━━━┯━━━━━┯━━━━━━┯━━━━━┓"
	+"\n┃  人名    │   外  号   │  赞同数  │   外  号   │  赞同数  │   外  号   │  赞同数  ┃"
	+"\n┠─────┴──────┴─────┴──────┴─────┴──────┴─────┨";
	
      	for( i = 0; i < sizeof(key); i++ ){
      		str += sprintf("\n┃%-2s"CYN"%-8s"NOR"：\t\t\t\t\t\t\t\t\t\t  ",cnumber[i], capitalize(key[i]) );
      		key2 = keys(artnames[key[i]]);
      		for( j = 0; j < sizeof(key2); j++ ){
      			if ( j%3 == 0 ) str += "┃\n┃\t    ";
      			str += sprintf("   %-10s      "HIW"%3d"NOR"    ",key2[j], sizeof(artnames[key[i]][key2[j]]));
      			if ( j > sizeof(key2)-2 ){
      				switch(j%3){
					case 0: str +="\t\t\t\t\t\t\t  ┃"; break;
					case 1: str +="\t\t\t  ┃"; break;
					case 2: str +="┃"; break;
					default: break;
				}
			}
		
      		}
      		str += "\n┠────────────────────────────────────────────┨";
      	}
      	
      	str += "\n┃请推举(artname)新的外号，如果赞同现有的，也请提议一次你所赞同的外号。                   ┃"
    	      +"\n┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
    	return str;
}

