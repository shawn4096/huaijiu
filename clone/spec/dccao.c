//Ilovemin 2016.5.3
#include <ansi.h>


inherit ITEM; 

void create()
{
	set_name (HIG"断肠草"NOR, ({ "duanchang cao"}));
	set("long","这是一株十年生的葫蔓藤科植物葫蔓藤，略带香味却含有极大的毒性。\n");

	set("unit","株");
	set_weight(100);
	set("value",3000000);
        set("no_cun", 1);
        set("no_give", 1);
        set("no_drop", 1);
	set("no_get", "这样东西不能离开那儿。\n");
	set("treasure",1);	
	set("degree",1);
	set("desc","据说是制作情花之毒解药的关键材料。");
	set("credit",50);
	setup();
}
