inherit ITEM;
void create()
{
        set_name("��վ�", ({ "shu", "book" }));
        set_weight(200);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ��𾭡�\n");
                set("value", 500);
                set("material", "paper");
                set("skill", ([
                        "name": "dacheng-fofa", // name of the skill
                        "exp_required": 0,      // minimum combat experience required
                        "jing_cost":    0,     // jing cost every time study this
                        "difficulty":   0,     // the base int to learn this skill
                        "max_skill":    201     // the maximum level you can learn
                ]) );
        }
}

