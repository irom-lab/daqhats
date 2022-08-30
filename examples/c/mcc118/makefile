TOPTARGETS := all clean

SUBDIRS := continuous_scan finite_scan finite_scan_with_trigger multi_hat_synchronous_scan single_value_read test_csv_logger single_value_read_lcm

$(TOPTARGETS): $(SUBDIRS)
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

.PHONY: $(TOPTARGETS) $(SUBDIRS)

