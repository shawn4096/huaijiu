
string look_leitai()
{
    	object me, room;
    	me = this_player();
    
    	if (me->is_busy()) 
          	return "����æ���ء�\n";
    	me->start_busy(2);
    	if (!(room = find_object(query("leitai"))))
          	room = load_object(query("leitai"));
        if( !room ) 
        	return "������̨û��׼���ã���֪ͨ��ʦ��\n";  
    	message_vision("$N������̨�ߣ��쳤�˲���������ȥ��\n", me);
    	"/cmds/std/look.c"->look_room(this_player(), room); 
    	return "";
}

int valid_leave(object me, string dir)
{
	object room;
	int i;
	
	if( dir != "out" && !wizardp(me)){
		if (!objectp(room = find_object(this_object()->query("exits/"+dir))))
          		room = load_object(this_object()->query("exits/"+dir));
          	
        	i = room->query_temp("num");
        	if( i > 15 ){
        		me->start_busy(1);
        		return notify_fail(room->query("short")+"�Ѿ�����Ϊ�����㼷����ȥ��\n");
        	}
        }
	if(query_temp("num")) add_temp("num", -1);
	return ::valid_leave(me,dir);
}

int do_action(string arg)
{
	this_player()->start_busy(2);
   	write("\n����Ҫ����������ͻȻ�������˽���һ�ģ��úÿ����䣬���Ҷ���\n\n");
   	return 1;
}
