// wear.c

#include <ansi.h>

inherit F_CLEAN_UP;

int do_wear(object me, object ob);

int main(object me, string arg)
{
	object ob, *inv;
	int i, count;

	if( !arg ) return notify_fail("��Ҫ����ʲô��\n");
    if (me->is_busy()) return notify_fail("����æ���ء�\n");

	if(arg=="all") {
		inv = all_inventory(me);
		for(count=0, i=0; i<sizeof(inv); i++) {
			if( inv[i]->query("equipped") ) continue;
			if(do_wear(me, inv[i]) ) count ++;
		}
        if (me->is_fighting() && count) me->start_busy(1);
		write("Ok.\n");
		return 1;
	}

	if( !objectp(ob = present(arg, me)) )
		return notify_fail("������û������������\n");

	if( ob->query("equipped") )
		return notify_fail("���Ѿ�װ�����ˡ�\n");

    count = do_wear(me, ob);
    if (me->is_fighting() && count) me->start_busy(1);
    return count;
}

int do_wear(object me, object ob)
{
	string str;

	if( ob->query("female_only")
	&&      (string)me->query("gender") =="����")
		return notify_fail("����Ů�˵���������һ��������Ҳ�봩����Ҳ���ߣ�\n");

	notify_fail("��ֻ�ܴ����ɵ������ߵĶ�����\n");
	if( ob->wear() ) {
		if( !stringp(str = ob->query("wear_msg")) )
			switch( ob->query("armor_type") ) {
				case "cloth":
				case "armor":
				case "boots":
					str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
					break;
				case "head":
				case "neck":
				case "wrists":
				case "finger":
				case "hands":
					str = YEL "$N����һ" + ob->query("unit") + "$n��\n" NOR;
					break;
				case "waist":
					str = YEL "$N��һ" + ob->query("unit") + "$n�������䡣\n" NOR;
					break;
				default:
					str = YEL "$Nװ����һ" + ob->query("unit") + "$n��\n" NOR;
			}
		message_vision(str, me, ob);
		return 1;
	}
	return 0;
}

int help(object me)
{
	write(@HELP
ָ���ʽ��wear <װ������>
 
���ָ������װ��ĳ�����ߡ�
 
HELP
    );
    return 1;
}
