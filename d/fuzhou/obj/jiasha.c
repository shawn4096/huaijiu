// jiasha.c
//Jay 4/8/96

inherit ITEM;
void setup()
{}

void init()
{
        add_action("do_move", "move");
}

void create()
{
        set_name("袈裟", ({"jia sha", "jia", "sha"}));
        set_weight(800);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一件旧得已经看不出颜色的袈裟，上面有好多窟窿。\n");
                set("unit", "件");
                set("material", "cloth");
                set("no_get", "这样东西不能离开那儿。\n");
        }
        setup();
}

int do_move(string arg)
{
        object book;
        object me = this_player();
        if (!id(arg))
                return 0;
        if (me->query("passwd")) {
                if (book = unew(__DIR__"kuihua")) {
			message_vision("$N轻轻地挪动袈裟，抖起一些尘土...，突然从袈裟的窟窿中掉出一件比较小的袈裟到$N怀中。\n", me);
			book->set("reader", me->query("id"));
			book->move(me);
			return 1;
                }
                message_vision(
"$N轻轻地挪动袈裟，抖起一些尘土，呛得$N直打喷嚏。\n", me);
                return 1;
        }
        else {
                message_vision("$N轻轻地挪动袈裟，突然从袈裟的窟窿中冒出一股毒气，钻进$N的鼻子中。\n", me);
                me->die();
                return 1;
        }
}
