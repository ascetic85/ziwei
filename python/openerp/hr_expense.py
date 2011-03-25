def expense_accept(self, cr, uid, ids, *args):
	# Anybody can not accept by themself
	userID = self.browse(cr, uid, ids)[0].user_id.id
	if userID == uid:
		raise osv.except_osv(_('Error !'), _('You can't accept yourself!'))
